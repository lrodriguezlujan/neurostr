#ifndef NEUROSTR_BASE_NEURON_H_
#define NEUROSTR_BASE_NEURON_H_

#include <string>
#include <map>
#include <exception>

#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/indirect_iterator.hpp>

#include "core/property.h"
#include "core/neurite_type.h"
#include "core/neurite.h"

namespace neurostr {
  
  
/**
*@brief lambda expresion to select axon
*/
const auto axon_neurite_filter = [](const auto & p) -> bool {
      return p.type() == NeuriteType::kAxon;
};

/**
*@brief lambda expresion to select basal dendrites
*/
const auto dendrite_neurite_filter = [](const auto & p) -> bool {
      return p.type() == NeuriteType::kDendrite;
};


/**
*@brief lambda expresion to select apical dendrites
*/
const auto apical_neurite_filter = [](const auto & p) -> bool {
    return p.type() == NeuriteType::kApical;
};


/**
 * @class Neuron
 * @author luis
 * @date 28/09/16
 * @file neuron.h
 * @brief 
 */
class Neuron : public WithProperties {
    
 public:
  
  // Traits
  typedef std::string id_type;

  // ITerators
  using neurite_iterator =
    typename boost::indirect_iterator<
      std::vector<std::unique_ptr<Neurite>>::iterator, 
      Neurite>;
      
  using const_neurite_iterator =
    typename boost::indirect_iterator<
      std::vector<std::unique_ptr<Neurite>>::const_iterator,
      const Neurite>;
      
  template <typename branch_iterator_t> 
  using node_iterator = Neurite::node_iterator<branch_iterator_t>;
  
  // Soma iters
  typedef typename std::vector<Node>::iterator soma_iterator;
  typedef typename std::vector<Node>::const_iterator const_soma_iterator;

  // Find in neurites
  typedef Neurite::branch_iterator branch_iterator;

  /**
   * @brief Empty constructor. Create a neuron with no id, neurites nor soma.
   * up vector is set to default value (0,0,1)
   * @return Neuron
   */
  Neuron() 
    : WithProperties()
    , id_()
    , neurites_()
    , soma_()
    , up_(0,0,1) {};
  
  /**
   * @brief Create a neuron with given id, and no neurites nor soma.
   * up vector is set to default value (0,0,1)
   * @param id Neuron id
   * @return Neuron
   */
  Neuron(const std::string& id) 
    : WithProperties()
    , id_(id)
    , neurites_()
    , soma_()
    , up_(0,0,1) {};
  
  /**
   * @brief Creates a neuron with given id and soma nodes. up vector is set to default value (0,0,1)
   * @param id Neuron id
   * @param soma Soma nodes
   * @return Neuron
   */
  Neuron(const std::string& id, const std::vector<Node>& soma)
      : WithProperties()
      , id_(id)
      , neurites_()
      , soma_(soma)
      , up_(0,0,1) {};

  private:
  
    std::string id_;
    std::vector<std::unique_ptr<Neurite>> neurites_;
    std::vector<Node> soma_;
    point_type up_;
  
  public:

  // Empy destr.
  ~Neuron() {};

  // Dont allow copy
  Neuron(const Neuron&) = delete;
  Neuron& operator=(const Neuron&) = delete;
  
  // Move
  Neuron(Neuron&&) = default;
  Neuron& operator=(Neuron&&) = default;

  /**
   * @brief Get neruon id
   * @return Node id string
   */
  const std::string& id() const { return id_; };
  
  /**
   * @brief Get neuron Up vector
   * @return Point
   */
  const point_type& up() const {return up_;}
  
  
  /**
   * @brief Set neuron up vector. Given vector is normalized
   * @param up New up vector 
   */
  void up(const point_type& up) {
    up_ = up;
    geometry::normalize(up_);
  }

  // Counts and other aux methods
  
  /**
   * @brief Count number of neurites
   * @return Neurite count
   */
  int size() const { return neurites_.size(); }
  
  /**
   * @brief Number of different nodes in the neuron
   * @return Node count
   */
  int node_count() const {
    int accum = 0;
    for (auto it = begin_neurite(); it != end_neurite(); ++it) 
      accum += it->node_count();
    return accum;
  }

  /**
   * @brief Add new neurite to the neuron
   * @param n Neurite pointer to be added
   * @return  Insert point
   */
  neurite_iterator add_neurite(Neurite* const n) {
    n->neuron(this);
    neurites_.emplace_back(n);
    return neurite_iterator(std::prev(neurites_.end(),1));
  }

  /**
   * @brief Add node set to soma
   * @param v Vector of nodes to add to the soma
   */
  void add_soma(const std::vector<Node>& v) { 
    soma_.insert(soma_.end(), v.begin(), v.end()); 
  }
  
  /**
   * @brief Add single node to soma
   * @param n Node to add
   */
  void add_soma(const Node& n) { soma_.push_back(n); }

  /*** Property management ***/
  
  /**
   * @brief Adds a proprety to the neuron and, optionally, to its neurites
   * @param key Property key
   * @param v Property value
   * @param recursive If true, property is also added to neuron neurites.
   */
  template <typename T> 
  auto add_property(const std::string& key, const T& v, bool recursive = false) {
    if (recursive){
      for(auto it = begin_neurite(); it != end_neurite(); ++it )
        it->add_property(key,v,true);
    }
    return properties.set(key,v);
  }

  /**
   * @brief Adds an empty proprety to the neuron and, optionally, to its neurites
   * @param key Property key
   * @param recursive If true, property is also added to neuron neurites.
   */
  auto add_property(const std::string& key, bool recursive = false) {
    if (recursive){
      for(auto it = begin_neurite(); it != end_neurite(); ++it )
        it->add_property(key,true);
    }
    return properties.set(key);
  }

  /***************************/

  /**
   * @brief Creates neurite iterator
   * @return Begin neurite iterator
   */
  neurite_iterator begin_neurite() { 
    return neurite_iterator(neurites_.begin()); 
  }
  
  /**
   * @brief Creates neurite iterator
   * @return End neurite iterator
   */
  neurite_iterator end_neurite() { 
    return neurite_iterator(neurites_.end()); 
  }

  /**
   * @brief Creates neurite iterator
   * @return Begin neurite iterator
   */
  const_neurite_iterator begin_neurite() const { 
    return const_neurite_iterator(neurites_.begin()); 
  }
  
  /**
   * @brief Creates neurite iterator
   * @return End neurite iterator
   */
  const_neurite_iterator end_neurite() const { 
    return const_neurite_iterator(neurites_.end()); 
  }

  /**
   * @brief Iterator over soma nodes
   * @return Begin soma iterator
   */
  soma_iterator begin_soma() { 
    return soma_.begin(); 
  }
  
  /**
   * @brief Iterator over soma nodes
   * @return End soma iterator
   */
  soma_iterator end_soma() { 
    return soma_.end(); 
  }

/**
   * @brief Iterator over soma nodes
   * @return Begin soma iterator
   */
  const_soma_iterator begin_soma() const { 
    return soma_.begin();
  }
  
  /**
   * @brief Iterator over soma nodes
   * @return End soma iterator
   */
  const_soma_iterator end_soma() const { 
    return soma_.end(); 
  }

  /**
   * @brief Iterator over axon. Axon is supposed to be unique...
   * @return Begin axon iterator
   */
  auto begin_axon() {
    return boost::filter_iterator<decltype(axon_neurite_filter), 
                                  neurite_iterator>(
        axon_neurite_filter, begin_neurite(), end_neurite());
  }

  /**
   * @brief Iterator over axon. Axon is supposed to be unique...
   * @return End axon iterator
   */
  auto end_axon() {
    return boost::filter_iterator<decltype(axon_neurite_filter), 
                                  neurite_iterator>(
        axon_neurite_filter, end_neurite(), end_neurite());
  }

  /**
   * @brief Iterator over apical. Apical is supposed to be unique...
   * @return Begin apical iterator
   */
  auto begin_apical() {
    return boost::filter_iterator<decltype(apical_neurite_filter), 
                                  neurite_iterator>(
        apical_neurite_filter, begin_neurite(), end_neurite());
  }

  /**
   * @brief Iterator over apical. Apical is supposed to be unique...
   * @return End apical iterator
   */
  auto end_apical() {
    return boost::filter_iterator<decltype(apical_neurite_filter), 
                                  neurite_iterator>(
        apical_neurite_filter, end_neurite(), end_neurite());
  }

  /**
   * @brief Iterator over basal dendrites
   * @return Begin basal dendrites iterator
   */
  auto begin_dendrite() {
    return boost::filter_iterator<decltype(dendrite_neurite_filter), 
                                  neurite_iterator>(
        dendrite_neurite_filter, begin_neurite(), end_neurite());
  }

  /**
   * @brief Iterator over basal dendrites
   * @return End basal dendrites iterator
   */
  auto end_dendrite() {
    return boost::filter_iterator<decltype(dendrite_neurite_filter), 
                                  neurite_iterator>(
        dendrite_neurite_filter, end_neurite(), end_neurite());
  }

  // Const versions
    /**
   * @brief Iterator over axon. Axon is supposed to be unique...
   * @return Begin axon iterator
   */
  auto begin_axon() const {
    return boost::filter_iterator<decltype(axon_neurite_filter), 
                                  const_neurite_iterator>(
        axon_neurite_filter, begin_neurite(), end_neurite());
  }

  /**
   * @brief Iterator over axon. Axon is supposed to be unique...
   * @return End axon iterator
   */
  auto end_axon() const {
    return boost::filter_iterator<decltype(axon_neurite_filter), 
                                  const_neurite_iterator>(
        axon_neurite_filter, end_neurite(), end_neurite());
  }

  /**
   * @brief Iterator over apical. Apical is supposed to be unique...
   * @return Begin apical iterator
   */
  auto begin_apical() const {
    return boost::filter_iterator<decltype(apical_neurite_filter), 
                                  const_neurite_iterator>(
        apical_neurite_filter, begin_neurite(), end_neurite());
  }

  /**
   * @brief Iterator over apical. Apical is supposed to be unique...
   * @return End apical iterator
   */
  auto end_apical() const {
    return boost::filter_iterator<decltype(apical_neurite_filter), 
                                  const_neurite_iterator>(
        apical_neurite_filter, end_neurite(), end_neurite());
  }

  /**
   * @brief Iterator over basal dendrites
   * @return Begin basal dendrites iterator
   */
  auto begin_dendrites() const {
    return boost::filter_iterator<decltype(dendrite_neurite_filter), 
                                  const_neurite_iterator>(
        dendrite_neurite_filter, begin_neurite(), end_neurite());
  }

  /**
   * @brief Iterator over basal dendrites
   * @return End basal dendrites iterator
   */
  auto end_dendrites() const {
    return boost::filter_iterator<decltype(dendrite_neurite_filter), 
                                  const_neurite_iterator>(
        dendrite_neurite_filter, end_neurite(), end_neurite());
  }

  // Counts by type
  
  /**
   * @brief Counts number of axon neuritesin the neuron
   * @return Number of axon
   */
  int axon_count() const { 
    return std::distance(begin_axon(), end_axon()); 
  }
  
  /**
   * @brief Counts number of apical neurites in the neuron
   * @return Number of apical
   */
  int apical_count() const { 
    return std::distance(begin_apical(), end_apical()); 
  }
  
  /**
   * @brief Counts number of basal dendrites in the neuron
   * @return Number of apical
   */
  int dendrite_count() const { 
    return std::distance(begin_dendrites(), end_dendrites()); 
  }
  
  /**
   * @brief Checks if the neuron soma is not empty
   * @return True if soma is not empty
   */
  bool has_soma() const { 
    return !soma_.empty(); 
  }

  /**
   * @brief Finds a node in the neuron. doesnt search in soma nodes
   * @param n Node to be found
   * @return Node iterator. IF node is not found returns the iterator created
   * by the empty constructor
   */
  Neurite::base_node_iterator find(const Node& n) {

    for (auto it = begin_neurite(); it != end_neurite(); ++it) {
      auto nodeit = it->find(n);
      if (nodeit != it->end_node()) return nodeit;
    }

    // Not valid
    return Neurite::base_node_iterator();
  }

  /**
   * @brief Finds a node in the neuron that matches the id. doesnt search in soma nodes
   * @param id Node Id
   * @return Node iterator. IF node is not found returns the iterator created
   * by the empty constructor
   */
 Neurite::base_node_iterator find(Node::id_type id) { 
    return find(Node(id)); 
  }

  /**
   * @brief Finds a node in the soma
   * @param n Node to be found
   * @return Iterator to the node. end_soma otherwise
   */
  soma_iterator find_soma(const Node& n) {
    auto it = std::find(soma_.begin(), soma_.end(), n);
    if (it != soma_.end())
      return soma_iterator(it);
    else
      return soma_iterator(soma_.end());
  }

   /**
   * @brief Finds a node in the soma by id
   * @param id ID of the node to be found
   * @return Iterator to the node. end_soma otherwise
   */
  soma_iterator find_soma(Node::id_type id) { return find_soma(Node(id)); }

  /**
   * @brief Checks if the given point is within the soma. The condition is
   * that the given point should be closer to the soma barycenter than at least
   * one point in the soma
   * @param p Point
   * @return True if point is considered to be in the soma
   **/
  bool point_in_soma(const point_type& p) const {

    // Criteria: point is in soma if
    // It is closer to the soma baricenter than at least one point of the soma contour
    point_type b = soma_barycenter();

    
    float dist = geometry::distance(p, b);

    for (auto it = soma_.begin(); it != soma_.end(); ++it) {
      if (geometry::distance(it->position(), b) < dist) 
        return true;
    }
    return false;
  }

  /**
   * @brief  TODO
   */
  void correct() {
    for (auto it = begin_neurite(); it != end_neurite(); ++it) {
      if (!it->has_root()) {
        auto n = it->begin_node();
        if (point_in_soma(n->position())) it->set_root(*n);
      }

      it->correct();
    }
  }
  
  /**
   * @brief Removes zero-length segements in all neurites
   */
  void remove_null_segments();
  
  /**
   * @brief Computes soma barycenter
   * @return soma barycenter
   */
  point_type soma_barycenter() const;

  /**
   * @brief Scales all nodes in the neuron by r
   * @param r scale rate
   */
  void scale(float r);
  
  /**
   * @brief Scales all nodes in the neuron by (rx,ry,rz)
   * @param rx x-axis scale
   * @param ry y-axis scale
   * @param rz z-axis scale
   */
  void scale( float rx, float ry, float rz);

  /**
   * @brief Moves all nodes in the neuron by p
   * @param p Traslation vector
   */
  void traslate(const point_type& p);

  /**
   * @brief rotates all nodes in the neuron
   * @param q rotation quaternion
   */
  void rotate(const Eigen::Quaternionf& q);
  
  /**
   * @brief Traslates the neuron so the soma barycenter lies at 0,0,0
   */
  void center();
  

  /**
   * @brief Rotates the neuron so the apical towards "up" direction
   */
  void set_apical_up();
  
  /**
   * @brief Rotates the neuron so the basal plane is close to the z=0 plane
   */
  void set_basal_roots_xz();
  
  /**
   * @brief Computes the axis-aligned bounding box
   * @return bounding box
   */
  box_type boundingBox();
  
  /**
   * @brief Computes soma area
   * @return Soma area
   */
  float somaArea();
  
  /**
   * @brief Order all neurites
   */
  void order();
  
  /**
   * @brief Applies RDP simplification to all branches in the neruon
   * @param eps Tolerance
   */
  void simplify(float eps = -1.5);

  // Output!
  friend std::ostream& operator<<(std::ostream&, const Neuron&);
  
  private:
  
    /**
     * @brief Applies the rotation that transform \code{from} to \code{to} to all
     * nodes in the neuron
     * @param from First vector
     * @param to Taget vector
     */
    void rotateAlign(const point_type& from, const point_type& to);
    
    /**
     * @brief Extract the position on every soma node
     * @return Position vector
     */
    std::vector<point_type> soma_positions() const;
    
    
};


/**
 * @class Reconstruction
 * @author luis
 * @date 28/09/16
 * @file neuron.h
 * @brief Reconstruction stores several neuron reconstructions as well as a common
 * contour
 */
class Reconstruction : public WithProperties{
  public:
  
  typedef polygon_type contour_type;
  typedef std::string id_type;
  
  using neuron_iterator = boost::indirect_iterator<
    std::vector<std::unique_ptr<Neuron>>::iterator, 
    Neuron>;
  
  using const_neuron_iterator =
      boost::indirect_iterator<
        std::vector<std::unique_ptr<Neuron>>::const_iterator,
        const Neuron>;
  
  /**
   * @brief Creates a reconsturction with no id, neurons nor contour
   */
  Reconstruction() : WithProperties(), id_(), neurons_(), contour_() {};
  
  /**
   * @brief Creates an empty reconstruction with given id
   * @param id Reconstruction ID
   */
  Reconstruction(const std::string& id) : WithProperties(), id_(id), neurons_(), contour_() {};
  
  ~Reconstruction() {} 

  // DO NOT ALLOW COPY (UNIQUE_PTR)
  Reconstruction(const Reconstruction&) = delete;
  Reconstruction& operator=(const Reconstruction&) = delete;

  // Move is ok
  Reconstruction(Reconstruction&&) = default;
  Reconstruction& operator=(Reconstruction&&) = default;

  // Data members
 private:
  std::string id_;
  std::vector<std::unique_ptr<Neuron>> neurons_;
  contour_type contour_;

  public:
  
  /**
   * @brief Adds a neuron to the reconstruction
   * @param n Neuron pointer
   */
  void addNeuron(Neuron* const n) {
    neurons_.emplace_back(n);
  };

  /**
   * @brief Sets a vector of points as reconstruction contour
   * @param v Point vector
   */
  void addContour(const std::vector<point_type>& v) {
    contour_ = geometry::as_planar_polygon(v);
  }

  friend std::ostream& operator<<(std::ostream&, const Reconstruction&);

  /**
   * @brief Get reconstruction contour as polygon
   * @return Reconstruction contour
   */
  const contour_type& contour() const { return contour_; }
  
  /**
   * @brief Get reconstruction ID
   * @return ID
   */
  const std::string& id() const { return id_; }
  
  /**
   * @brief Checks whether the contour is empty
   * @return True if contour is not empty
   */
  bool has_contour() const { return geometry::num_points(contour_) > 0; }
  
  /**
   * @brief Counts number of neurons in the reconstruction
   * @return Neuron count
   */
  int size() const { return neurons_.size(); }
  
  /**
   * @brief Counts number of different nodes in the reconstruction
   * @return Node count
   */
  int node_count() const {
    int accum = 0;
    for (auto it = begin(); it != end(); ++it) accum += it->node_count();
    return accum;
  }

  /**
   * @brief Finds the neuron whose soma is the closest one to a given point
   * @param p Point
   * @return Neuron iterator
   */
  neuron_iterator closest_soma(const point_type& p) {
    auto ret = end();
    float tmp, min_dist = std::numeric_limits<float>().max();
    for (auto it = begin(); it != end(); ++it) {
      for (auto s_it = it->begin_soma(); s_it != it->end_soma() && ret != it; ++s_it) {
        tmp = s_it->distance(p);
        if (tmp < min_dist) {
          ret = it;
          min_dist = tmp;
        }
      }
    }
    return ret;
  }

  /**
   * @brief Adds a neurite to the neuron whose soma is the closest one to the
   * neurite root
   * @param n Neurite pointer
   * @return Neuron iterator (insertion point)
   */
  neuron_iterator add_neurite_to_closest_soma(Neurite* n) {
        
    auto closest = closest_soma(n->has_root()?(n->root().position()):(n->begin_node()->position()));
    
    if (closest == end()) {
      throw std::runtime_error("Orphan neurite");
    } else {
      n->id(closest->size() + 1);
      closest->add_neurite(n);
    }
    return closest;
  }
  
  /**
   * @brief Neuron iterator
   * @return begin neuron interator
   */
  neuron_iterator begin() { 
    return neuron_iterator(neurons_.begin()); 
  }
  
  /**
   * @brief Neuron iterator
   * @return end neuron interator
   */
  neuron_iterator end() { 
    return neuron_iterator(neurons_.end()); 
  }
  
  /**
   * @brief Neuron iterator
   * @return begin neuron interator
   */
  const_neuron_iterator begin() const { 
    return const_neuron_iterator(neurons_.begin()); 
  }
  
  /**
   * @brief Neuron iterator
   * @return end neuron interator
   */
  const_neuron_iterator end() const {
    return const_neuron_iterator(neurons_.end()); 
  }
  
};

std::ostream& operator<<(std::ostream& os, const Reconstruction& r);
std::ostream& operator<<(std::ostream& os, const Neuron& n);

}  // namespace neruostr

#endif
