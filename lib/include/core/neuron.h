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
  
  
// Filters
auto axon_neurite_filter = [](const auto & p) -> bool {
      return p.type() == NeuriteType::kAxon;
};

auto dendrite_neurite_filter = [](const auto & p) -> bool {
      return p.type() == NeuriteType::kDendrite;
};

auto apical_neurite_filter = [](const auto & p) -> bool {
    return p.type() == NeuriteType::kApical;
};



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

  // Basic constructors
  Neuron() 
    : WithProperties()
    , id_()
    , neurites_()
    , soma_()
    , up_(0,0,1) {};
  
  Neuron(const std::string& id) 
    : WithProperties()
    , id_(id)
    , neurites_()
    , soma_()
    , up_(0,0,1) {};
  
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

  ~Neuron() {};

  // We allow copy -> shared ptrs
  Neuron(const Neuron&) = default;
  Neuron& operator=(const Neuron&) = default;
  Neuron(Neuron&&) = default;
  Neuron& operator=(Neuron&&) = default;

  // Access
  const std::string& id() const { return id_; };
  const point_type& up() const {return up_;}
  
  
  // Set
  void up(const point_type& up) {up_ = up;}

  // Counts and other aux methods
  
  // Number of neurites
  int size() const { return neurites_.size(); }
  
  int node_count() const {
    int accum = 0;
    for (auto it = begin_neurite(); it != end_neurite(); ++it) 
      accum += it->node_count();
    return accum;
  }

  // Add neurites
  neurite_iterator add_neurite(Neurite* const n) {
    n->neuron(this);
    neurites_.emplace_back(n);
    return neurite_iterator(--neurites_.end());
  }

  // Add soma points / point
  void add_soma(const std::vector<Node>& v) { 
    soma_.insert(soma_.end(), v.begin(), v.end()); 
  }
  
  void add_soma(const Node& n) { soma_.push_back(n); }

  /*** Property management ***/

  template <typename T> 
  auto add_property(const std::string& key, const T& v, bool recursive = false) {
    if (recursive){
      for(auto it = begin_neurite(); it != end_neurite(); ++it )
        it->add_property(key,v,true);
    }
    return properties.set(key,v);
  }

  auto add_property(const std::string& key, bool recursive = false) {
    if (recursive){
      for(auto it = begin_neurite(); it != end_neurite(); ++it )
        it->add_property(key,true);
    }
    return properties.set(key);
  }

  /***************************/

  // Base Iterators
  neurite_iterator begin_neurite() { 
    return neurite_iterator(neurites_.begin()); 
  }
  neurite_iterator end_neurite() { 
    return neurite_iterator(neurites_.end()); 
  }

  const_neurite_iterator begin_neurite() const { 
    return const_neurite_iterator(neurites_.begin()); 
  }
  const_neurite_iterator end_neurite() const { 
    return const_neurite_iterator(neurites_.end()); 
  }

  soma_iterator begin_soma() { 
    return soma_.begin(); 
  }
  soma_iterator end_soma() { 
    return soma_.end(); 
  }

  const_soma_iterator begin_soma() const { 
    return soma_.begin();
  }
  
  const_soma_iterator end_soma() const { 
    return soma_.end(); 
  }

  // Typed iterators (sugar) - the re made using boost filter iterator
  auto begin_axon() {
    return boost::filter_iterator<decltype(axon_neurite_filter), 
                                  neurite_iterator>(
        axon_neurite_filter, begin_neurite(), end_neurite());
  }

  auto end_axon() {
    return boost::filter_iterator<decltype(axon_neurite_filter), 
                                  neurite_iterator>(
        axon_neurite_filter, end_neurite(), end_neurite());
  }

  auto begin_apical() {
    return boost::filter_iterator<decltype(apical_neurite_filter), 
                                  neurite_iterator>(
        apical_neurite_filter, begin_neurite(), end_neurite());
  }

  auto end_apical() {
    return boost::filter_iterator<decltype(apical_neurite_filter), 
                                  neurite_iterator>(
        apical_neurite_filter, end_neurite(), end_neurite());
  }

  auto begin_dendrite() {
    return boost::filter_iterator<decltype(dendrite_neurite_filter), 
                                  neurite_iterator>(
        dendrite_neurite_filter, begin_neurite(), end_neurite());
  }

  auto end_dendrite() {
    return boost::filter_iterator<decltype(dendrite_neurite_filter), 
                                  neurite_iterator>(
        dendrite_neurite_filter, end_neurite(), end_neurite());
  }

  // Const
  auto begin_axon() const {
    return boost::filter_iterator<decltype(axon_neurite_filter), 
                                  const_neurite_iterator>(
        axon_neurite_filter, begin_neurite(), end_neurite());
  }

  auto end_axon() const {
    return boost::filter_iterator<decltype(axon_neurite_filter), 
                                  const_neurite_iterator>(
        axon_neurite_filter, end_neurite(), end_neurite());
  }

  auto begin_apical() const {
    return boost::filter_iterator<decltype(apical_neurite_filter), 
                                  const_neurite_iterator>(
        apical_neurite_filter, begin_neurite(), end_neurite());
  }

  auto end_apical() const {
    return boost::filter_iterator<decltype(apical_neurite_filter), 
                                  const_neurite_iterator>(
        apical_neurite_filter, end_neurite(), end_neurite());
  }

  auto begin_dendrites() const {
    return boost::filter_iterator<decltype(dendrite_neurite_filter), 
                                  const_neurite_iterator>(
        dendrite_neurite_filter, begin_neurite(), end_neurite());
  }

  auto end_dendrites() const {
    return boost::filter_iterator<decltype(dendrite_neurite_filter), 
                                  const_neurite_iterator>(
        dendrite_neurite_filter, end_neurite(), end_neurite());
  }

  // Counts
  int axon_count() const { 
    return std::distance(begin_axon(), end_axon()); 
  }
  
  int apical_count() const { 
    return std::distance(begin_apical(), end_apical()); 
  }
  
  int dendrite_count() const { 
    return std::distance(begin_dendrites(), end_dendrites()); 
  }
  
  bool has_soma() const { 
    return !soma_.empty(); 
  }


  Neurite::base_node_iterator find(const Node& n) {

    for (auto it = begin_neurite(); it != end_neurite(); ++it) {
      auto nodeit = it->find(n);
      if (nodeit != it->end_node()) return nodeit;
    }

    // Not valid
    return Neurite::base_node_iterator();
  }

 Neurite::base_node_iterator find(Node::id_type id) { 
    return find(Node(id)); 
  }

  // Find in soma
  soma_iterator find_soma(const Node& n) {
    auto it = std::find(soma_.begin(), soma_.end(), n);
    if (it != soma_.end())
      return soma_iterator(it);
    else
      return soma_iterator(soma_.end());
  }

  soma_iterator find_soma(Node::id_type id) { return find_soma(Node(id)); }

  // Function that checks if a given point is in the soma
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

  // Ceck neuron correctness
  void correct() {
    for (auto it = begin_neurite(); it != end_neurite(); ++it) {
      if (!it->has_root()) {
        auto n = it->begin_node();
        if (point_in_soma(n->position())) it->set_root(*n);
      }

      it->correct();
    }
  }
  
  void remove_null_segments();
  
  // Soma baricenter
  point_type soma_barycenter() const;

  // Scale
  void scale(float r);
  void scale( float rx, float ry, float rz);

  // Traslate
  void traslate(const point_type& p);

  // Rotate
  void rotate(const Eigen::Quaternionf& q);
  
  // Center
  void center();
  
  // Orient apical towards "up" direction
  void set_apical_up();
  
  // Basalroots in xz plane
  void set_basal_roots_xz();
  
  // Axis aligned bounding box
  box_type boundingBox();
  
  // Compute soma planar area
  float somaArea();
  
  // Order
  void order();
  void simplify(float eps = -1.5);

  // Output!
  friend std::ostream& operator<<(std::ostream&, const Neuron&);
  
  private:
    void rotateAlign(const point_type& from, const point_type& to);
    std::vector<point_type> soma_positions() const;
    
    
};


// FWD Defs

// Sometimes we get several reconstructions in the same ASC/DAT file
// as well as a sample contour
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

  // Constructor destructors
  Reconstruction() : WithProperties(), id_(), neurons_(), contour_() {};
  Reconstruction(const std::string& id) : WithProperties(), id_(id), neurons_(), contour_() {};
  ~Reconstruction() {}  // shared_ptrs own the objs

  // DO NOT ALLOW COPY
  Reconstruction(const Reconstruction&) = delete;
  Reconstruction& operator=(const Reconstruction&) = delete;

  // Move is ok
  Reconstruction(Reconstruction&&) = default;
  Reconstruction& operator=(Reconstruction&&) = default;

  // Data member
 private:
  std::string id_;
  std::vector<std::unique_ptr<Neuron>> neurons_;
  contour_type contour_;

 public:
  // Adds
  void addNeuron(Neuron* const n) {
    neurons_.emplace_back(n);
  };

  void addContour(const std::vector<point_type>& v) {
    contour_ = geometry::as_planar_polygon(v);
  }

  friend std::ostream& operator<<(std::ostream&, const Reconstruction&);

  const contour_type& contour() const { return contour_; }
  const std::string& id() const { return id_; }
  bool has_contour() const { return geometry::num_points(contour_) > 0; }
  int size() const { return neurons_.size(); }
  int node_count() const {
    int accum = 0;
    for (auto it = begin(); it != end(); ++it) accum += it->node_count();
    return accum;
  }

  // Closest soma to a given point
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

  /*** Property management ***/
  neuron_iterator begin() { 
    return neuron_iterator(neurons_.begin()); 
  }
  neuron_iterator end() { 
    return neuron_iterator(neurons_.end()); 
  }
  const_neuron_iterator begin() const { 
    return const_neuron_iterator(neurons_.begin()); 
  }
  const_neuron_iterator end() const {
    return const_neuron_iterator(neurons_.end()); 
  }
};

std::ostream& operator<<(std::ostream& os, const Reconstruction& r);
std::ostream& operator<<(std::ostream& os, const Neuron& n);

}  // namespace neruostr

#endif
