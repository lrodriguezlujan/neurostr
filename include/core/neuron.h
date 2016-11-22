#ifndef NEUROSTR_BASE_NEURON_H_
#define NEUROSTR_BASE_NEURON_H_

#include <string>
#include <map>
#include <exception>

#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/indirect_iterator.hpp>

#include "core/property.h"
#include "core/contour.h"
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
 * @file neuron.h
 * @brief Class that represents a single neuron, its soma and neurites, in the 
 * reconstruction.
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
  Neuron() ;
  
  /**
   * @brief Create a neuron with given id, and no neurites nor soma.
   * up vector is set to default value (0,0,1)
   * @param id Neuron id
   * @return Neuron
   */
  Neuron(const std::string& id);
  
  /**
   * @brief Creates a neuron with given id and soma nodes. up vector is set to default value (0,0,1)
   * @param id Neuron id
   * @param soma Soma nodes
   * @return Neuron
   */
  Neuron(const std::string& id, const std::vector<Node>& soma);

  private:
  
    std::string id_;
    std::vector<std::unique_ptr<Neurite>> neurites_;
    std::vector<Node> soma_;
    point_type up_;
  
  public:

  /**
   * @brief Default destructor
   */
  ~Neuron() {};

  /**
   * @brief Deleted
   * @warning DELETED
   */
  Neuron(const Neuron&) = delete;
  
  /**
   * @brief Deleted
   * @warning DELETED
   */
  Neuron& operator=(const Neuron&) = delete;
  
  /**
   * @brief Default implementation
   */
  Neuron(Neuron&&) = default;
  
  /**
   * @brief Default implementation
   */
  Neuron& operator=(Neuron&&) = default;

  /**
   * @brief Get neuron id string
   * @return Neuron id string
   */
  const std::string& id() const { return id_; };
  
  /**
   * @brief Get neuron Up vector. Up vector allows us to orient angles in 3D space
   * @return Point
   */
  const point_type& up() const {return up_;}
  
  
  /**
   * @brief Set neuron up vector. Given vector is normalized
   * @param up New up vector 
   */
  void up(const point_type& up);

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
  int node_count() const ;

  /**
   * @brief Add new neurite to the neuron
   * @param n Neurite pointer to be added
   * @return  Insert point
   */
  neurite_iterator add_neurite(Neurite* const n) ;

  /**
   * @brief Add node set to soma
   * @param v Vector of nodes to add to the soma
   */
   // This should be templated and done with iterators
  void add_soma(const std::vector<Node>& v);
  
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
  neurite_iterator begin_neurite(){return neurite_iterator(neurites_.begin());} 
  
  /**
   * @brief Creates neurite iterator
   * @return End neurite iterator
   */
  neurite_iterator end_neurite() {return neurite_iterator(neurites_.end());}

  /**
   * @brief Creates neurite iterator
   * @return Begin neurite iterator
   */
  const_neurite_iterator begin_neurite() const {return const_neurite_iterator(neurites_.begin());}
  
  /**
   * @brief Creates neurite iterator
   * @return End neurite iterator
   */
  const_neurite_iterator end_neurite() const {return const_neurite_iterator(neurites_.end());}

  /**
   * @brief Iterator over soma nodes
   * @return Begin soma iterator
   */
  soma_iterator begin_soma() {return soma_.begin();}
  
  /**
   * @brief Iterator over soma nodes
   * @return End soma iterator
   */
  soma_iterator end_soma() {return soma_.end();}

/**
   * @brief Iterator over soma nodes
   * @return Begin soma iterator
   */
  const_soma_iterator begin_soma() const { return soma_.begin();}
  
  /**
   * @brief Iterator over soma nodes
   * @return End soma iterator
   */
  const_soma_iterator end_soma() const { return soma_.end(); }

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
  int axon_count() const { return std::distance(begin_axon(), end_axon()); }
  
  /**
   * @brief Counts number of apical neurites in the neuron
   * @return Number of apical
   */
  int apical_count() const {return std::distance(begin_apical(), end_apical());}
  
  /**
   * @brief Counts number of basal dendrites in the neuron
   * @return Number of apical
   */
  int dendrite_count() const {return std::distance(begin_dendrites(), end_dendrites());}
  
  /**
   * @brief Checks if the neuron soma is not empty
   * @return True if soma is not empty
   */
  bool has_soma() const {return !soma_.empty();}

  /**
   * @brief Finds a node in the neuron. doesnt search in soma nodes
   * @param n Node to be found
   * @return Node iterator. IF node is not found returns the iterator created
   * by the empty constructor
   */
  Neurite::base_node_iterator find(const Node& n);

  /**
   * @brief Finds a node in the neuron that matches the id. doesnt search in soma nodes
   * @param id Node Id
   * @return Node iterator. IF node is not found returns the iterator created
   * by the empty constructor
   */
 Neurite::base_node_iterator find(Node::id_type id) { return find(Node(id)); }

  /**
   * @brief Finds a node in the soma
   * @param n Node to be found
   * @return Iterator to the node. end_soma otherwise
   */
  soma_iterator find_soma(const Node& n);

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
  bool point_in_soma(const point_type& p) const ;

  /**
   * @brief Correct function calls the correct function over each. Additionaly
   * checks if the neurite root is part of the soma and set is as such if necessary.
   */
  void correct();
  
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
   * @brief Removes a neurite from the neuron
   * @param n Neurite iterator
   * @return updated iterator
   */
  neurite_iterator erase(const neurite_iterator& n);
  
  /**
   * @brief Removes all axon neurites from the neuron
   */
  void erase_axon();
  
  /**
   * @brief Removes all apical dendrties from the neuron
   */
  void erase_apical();
  
  /**
   * @brief Removes all non-apical dendrties from the neuron
   */
  void erase_dendrites();
  
  /**
   * @brief Rotates the neuron so the apical towards "up" direction
   */
  void set_apical_up();
  
  /**
   * @brief Rotates the neuron so the basal plane is close to the z=0 plane
   */
  void set_basal_roots_xz();
  
  /**
   * @brief Computes the axis-aligned bounding box of the neuron
   * @return bounding box
   */
  box_type boundingBox();
  
  /**
   * @brief Computes soma area
   * @return Soma area
   */
  float somaArea() const;
  
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
 * @file neuron.h
 * @brief Reconstruction stores several neuron as well as common contours
 */
class Reconstruction : public WithProperties{
  public:
  
  using contour_type = Contour;
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
  Reconstruction() ;
  
  /**
   * @brief Creates an empty reconstruction with given id
   * @param id Reconstruction ID
   */
  Reconstruction(const std::string& id);
  
  /**
   * @brief Default
   */
  ~Reconstruction() {} 

  /**
   * @brief Not allowed
   * @warning DELETED
   */
  Reconstruction(const Reconstruction&) = delete;
  
  /**
   * @brief Not allowed
   * @warning DELETED
   */
  Reconstruction& operator=(const Reconstruction&) = delete;

  /**
   * @brief Default
   */
  Reconstruction(Reconstruction&&) = default;
  
  /**
   * @brief Default
   */
  Reconstruction& operator=(Reconstruction&&) = default;

  // Data members
 private:
  std::string id_;
  std::vector<std::unique_ptr<Neuron>> neurons_;
  
  std::vector<contour_type> contours_;

  public:
  
  /**
   * @brief Adds a neuron to the reconstruction
   * @param n Neuron pointer
   */
  void addNeuron(Neuron* const n) { 
    if(n!=nullptr)
      neurons_.emplace_back(n); 
  };

  /**
   * @brief Sets a vector of points as reconstruction contour
   * @param v Point vector
   */
  void addContour(const contour_type& v);

  friend std::ostream& operator<<(std::ostream&, const Reconstruction&);

  /**
   * @brief Get reconstruction contour as polygon
   * @return Reconstruction contour
   */
  std::vector<contour_type>::const_iterator contour_begin() const { return contours_.begin(); }
  std::vector<contour_type>::const_iterator contour_end() const { return contours_.end(); }
  
  /**
   * @brief Get reconstruction ID
   * @return ID
   */
  const std::string& id() const { return id_; }
  
  /**
   * @brief Checks whether the contour is empty
   * @return True if contour is not empty
   */
  std::size_t n_contours() const { return contours_.size(); }
  
  /**
   * @brief Counts number of neurons in the reconstruction
   * @return Neuron count
   */
  int size() const { return neurons_.size(); }
  
  /**
   * @brief Counts number of different nodes in the reconstruction
   * @return Node count
   */
  int node_count() const ;

  /**
   * @brief Finds the neuron whose soma is the closest one to a given point
   * @param p Point
   * @return Neuron iterator
   */
  neuron_iterator closest_soma(const point_type& p);

  /**
   * @brief Adds a neurite to the neuron whose soma is the closest one to the
   * neurite root
   * @param n Neurite pointer
   * @return Neuron iterator (insertion point)
   */
  neuron_iterator add_neurite_to_closest_soma(Neurite* n);
  
  /**
   * @brief Neuron iterator
   * @return begin neuron interator
   */
  neuron_iterator begin() { return neuron_iterator(neurons_.begin()); }
  
  /**
   * @brief Neuron iterator
   * @return end neuron interator
   */
  neuron_iterator end() { return neuron_iterator(neurons_.end()); }
  
  /**
   * @brief Neuron iterator
   * @return begin neuron interator
   */
  const_neuron_iterator begin() const { return const_neuron_iterator(neurons_.begin()); }
  
  /**
   * @brief Neuron iterator
   * @return end neuron interator
   */
  const_neuron_iterator end() const { return const_neuron_iterator(neurons_.end()); }
  
};

std::ostream& operator<<(std::ostream& os, const Reconstruction& r);
std::ostream& operator<<(std::ostream& os, const Neuron& n);

}  // namespace neruostr

#endif
