#include "core/neuron.h"
#include "core/log.h"

#include <limits>


#include <boost/any.hpp>
#include <boost/geometry/geometry.hpp>


namespace neurostr {

 /****************
 * 
 * Neuron
 * 
 *****************/
 
  // Constructors
  Neuron::Neuron() 
    : WithProperties()
    , id_()
    , neurites_()
    , soma_()
    , up_(0,0,1) {};
  

  Neuron::Neuron(const std::string& id) 
    : WithProperties()
    , id_(id)
    , neurites_()
    , soma_()
    , up_(0,0,1) {};
  
  Neuron::Neuron(const std::string& id, const std::vector<Node>& soma)
      : WithProperties()
      , id_(id)
      , neurites_()
      , soma_(soma)
      , up_(0,0,1) {};
      
  void Neuron::up(const point_type& up) {
    up_ = up;
    geometry::normalize(up_);
  }
  
  int Neuron::node_count() const {
    int accum = 0;
    for (auto it = begin_neurite(); it != end_neurite(); ++it) 
      accum += it->node_count();
    return accum;
  }
  
  Neuron::neurite_iterator Neuron::add_neurite(Neurite* const n) {
    n->neuron(this);
    neurites_.emplace_back(n);
    return neurite_iterator(std::prev(neurites_.end(),1));
  }
  
  void  Neuron::add_soma(const std::vector<Node>& v) { 
    soma_.insert(soma_.end(), v.begin(), v.end()); 
  }
  
  Neurite::base_node_iterator Neuron::find(const Node& n) {

    for (auto it = begin_neurite(); it != end_neurite(); ++it) {
      auto nodeit = it->find(n);
      if (nodeit != it->end_node()) return nodeit;
    }

    // Not valid
    return Neurite::base_node_iterator();
  }
  
  Neuron::soma_iterator Neuron::find_soma(const Node& n) {
    auto it = std::find(soma_.begin(), soma_.end(), n);
    if (it != soma_.end())
      return soma_iterator(it);
    else
      return soma_iterator(soma_.end());
  }
  
  bool Neuron::point_in_soma(const point_type& p) const {

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
  
  void Neuron::correct() {
    for (auto it = begin_neurite(); it != end_neurite(); ++it) {
      if (!it->root_is_soma()) {
        auto n = it->begin_branch()->begin();
        if (point_in_soma(n->position())){
          NSTR_LOG_(trace) << "Setting first node as root";
          it->set_root(*n);
          // Remove it
          //it->begin_branch()->erase( n );
        }
      }

      it->correct();
    }
  }

  
  std::vector<point_type> Neuron::soma_positions() const {
    std::vector<point_type> v(soma_.size());
    for(auto it = soma_.begin(); it != soma_.end(); ++it)
      v.push_back(it->position());
    return v;
  }
  
    // Soma baricenter
  point_type Neuron::soma_barycenter() const{
    return geometry::barycenter(soma_positions());
  }

  // Scale
  void Neuron::scale(float r){
    
    // First neurites
    for(auto it = begin_neurite(); it != end_neurite(); ++it)
      it->scale(r);
      
    // Then soma
    auto p = soma_barycenter();
    for( auto it = begin_soma(); it!= end_soma(); ++it )
      it->scale(r,p);
  }
  
  // Axis scale corrections
  void Neuron::scale( float rx, float ry, float rz){
    
    // Do it for neurites
    for(auto it = begin_neurite(); it != end_neurite(); ++it)
      it->scale(rx,ry,rz);
      
    // Do it for the soma nodes
    for( auto it = begin_soma(); it!= end_soma(); ++it )
      it->scale(rx,ry,rz);
  }

  // Traslate
  void Neuron::traslate(const point_type& p){
    // Neurites
    for(auto it = begin_neurite(); it != end_neurite(); ++it)
      it->traslate(p);
    
    // Soma
    for( auto it = begin_soma(); it!= end_soma(); ++it )
      it->traslate(p);
  }

  // Rotate
  void Neuron::rotate(const Eigen::Quaternionf& q){
    // Neurites
    for(auto it = begin_neurite(); it != end_neurite(); ++it)
      it->rotate(q);
    
    // Soma
    for( auto it = begin_soma(); it!= end_soma(); ++it )
      it->rotate(q);
  }
  
  void Neuron::center() {
    auto p = soma_barycenter();
    
    // Dont move if it not needed
    if( geometry::distance(p, point_type(0,0,0)) > 1E-3 ){
      geometry::negate(p);
      traslate(p);
    }
  }
  
    /**
   * @brief Removes a neurite from the neuron
   * @param n Neurite iterator
   * @return updated iterator
   */
  Neuron::neurite_iterator Neuron::erase(const neurite_iterator& n){
    return neurites_.erase(n.base());
  }
  
  /**
   * @brief Removes all axon neurites from the neuron
   */
  void Neuron::erase_axon(){
    for(auto it = begin_neurite(); it != end_neurite(); ++it){
      if(it->type() == NeuriteType::kAxon){
        it = std::prev(erase(it),1);
      }
    }
  }
  
  /**
   * @brief Removes all apical dendrties from the neuron
   */
  void Neuron::erase_apical(){
    for(auto it = begin_neurite(); it != end_neurite(); ++it){
      if(it->type() == NeuriteType::kApical){
        it = std::prev(erase(it),1);
      }
    }
  }
  
  /**
   * @brief Removes all non-apical dendrties from the neuron
   */
  void Neuron::erase_dendrites(){
    for(auto it = begin_neurite(); it != end_neurite(); ++it){
      if(it->type() == NeuriteType::kDendrite){
        it = std::prev(erase(it),1);
      }
    }
  }
  
  // Orient apical towards "up" direction
  // Todo...all nodes or just terminals?
  void Neuron::set_apical_up(){
    
    //TODO
    return ;
    /*// Center soma
    center();
    
    auto measure = measures::node::nodeset_avg_orientation(point_type(0,0,0));
    measures::Measure<decltype(measure), void> m(measure);
    
    auto sel = selector::neurite_node_selector(begin_apical());
    point_type avg_dir = m.measure(sel.begin(),sel.end());
    
    // Align avg_dir with up
    rotate(geometry::align_vectors(avg_dir,up_));*/
  }
  
  void Neuron::set_basal_roots_xz(){
  
    // Center soma
    center();
    
    // PCA
    // if(begin_dendrites() == end_dendrites() ) return;
    auto n = std::distance(begin_dendrites(), end_dendrites());
    if( n < 3 ) return ;
    
    // Create nx3 matrix
    Eigen::Matrix<double, Eigen::Dynamic, 3> m;
    
    m.resize(n, 3);
    
    // Fill it
    int i = 0;
    for (auto it = begin_dendrites(); it != end_dendrites(); ++it, ++i) {
      if(it->has_root()){
        m(i, 0) = it->root().x();
        m(i, 1) = it->root().y();
        m(i, 2) = it->root().z();
      }
      else 
        --n;
    } 
    
    // Then perform jacobisvd
    Eigen::JacobiSVD<decltype(m)> svd(m, Eigen::ComputeFullV);
    Eigen::Matrix<double, Eigen::Dynamic, 3> aux = svd.matrixV();  
    auto data = aux.data(); 

    // Align dir with up
    rotate(geometry::align_vectors(point_type(data[6],data[7],data[8]) ,up_));
  }
  
  void Neuron::remove_null_segments(){
    for(auto it = begin_neurite(); it != end_neurite(); ++it)
      it->remove_null_segments();
  }
  
  // Axis aligned bounding box
  box_type Neuron::boundingBox(){
    
    // Initialize limits
    point_type min_corner( std::numeric_limits<float>::max(),
                           std::numeric_limits<float>::max(), 
                           std::numeric_limits<float>::max());
    
    point_type max_corner( std::numeric_limits<float>::min(),
                           std::numeric_limits<float>::min(), 
                           std::numeric_limits<float>::min());
                           
    
    for(auto it = begin_neurite(); it != end_neurite(); ++it){
      for( auto n_it = it->begin_node(); n_it != it->end_node(); ++n_it ) {
        geometry::max_by_component(n_it->position(),max_corner);
        geometry::min_by_component(n_it->position(),min_corner);
      }
    }
    
    for(auto it = begin_soma(); it != end_soma(); ++it){
        geometry::max_by_component(it->position(),max_corner);
        geometry::min_by_component(it->position(),min_corner);
    }
    
    return box_type(min_corner,max_corner);
  }
  
  // Compute soma planar area
  float Neuron::somaArea() const{
    return geometry::polygon_area(geometry::as_planar_polygon(soma_positions()));
  }

  void Neuron::order(){
    /*for(auto it = begin_neurite(); it != end_neurite(); ++it)
      it->childOrder();*/
  }
  
  void Neuron::simplify(float eps){
    for(auto it = begin_neurite(); it != end_neurite(); ++it)
      it->simplify(eps);
  }
  
  // Print neuron
std::ostream& operator<<(std::ostream& os, const Neuron& n) {
  // Print * line
  os << std::string(50, '*') << std::endl;

  // Print ID:
  os << "Neuron ID: " << n.id_ << std::endl;

  // Print Number of  neurites
  if (n.neurites_.size() > 0) os << n.neurites_.size() << " neurites" << std::endl;

  // Print metadata/properties
  if (n.properties.size() > 0) {
    os << "Properties: " << std::endl;
    for (auto it = n.properties.begin(); it != n.properties.end(); ++it) {
      if (PropertyMap::empty(*it))
        os << "\t" << it->first << std::endl;
      else
        os << "\t" << PropertyMap::key(*it) << ": " << PropertyMap::value_as_string(*it) << std::endl;
    }
  }

  // Contour
  if (n.soma_.size() > 0) {
    os << "Cell body contour:" << std::endl;
    for (auto it = n.begin_soma(); it != n.end_soma(); ++it) {
      os << "\t" << (*it) << std::endl;
    }
  }

  // Print neurites
  if (n.size() > 0) {
    os << "Neurites:" << std::endl << std::endl;
    for (auto it = n.begin_neurite(); it != n.end_neurite(); ++it) {
      os << *it << std::endl;
    }
  }

  // Print * line
  os << std::string(50, '*') << std::endl;

  return os;
};


/****************
 * 
 * Reconstruction
 * 
 *****************/
 
Reconstruction::Reconstruction() : WithProperties(), id_(), neurons_(), contour_() {};
  
Reconstruction::Reconstruction(const std::string& id) : WithProperties(), id_(id), neurons_(), contour_() {};

void Reconstruction::addContour(const std::vector<point_type>& v) {
    contour_ = geometry::as_planar_polygon(v);
}

int Reconstruction::node_count() const {
    int accum = 0;
    for (auto it = begin(); it != end(); ++it) accum += it->node_count();
    return accum;
}

Reconstruction::neuron_iterator Reconstruction::closest_soma(const point_type& p) {
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

Reconstruction::neuron_iterator Reconstruction::add_neurite_to_closest_soma(Neurite* n) {
        
    // Special case - just 1 neuron
    neuron_iterator closest;
    
    if(size() == 1){
      closest = begin();
    } else {
      closest = closest_soma(n->has_root()?(n->root().position()):(n->begin_node()->position()));
    }
    
    if (closest == end()) {
      throw std::runtime_error("No neuron in reconstruction");
    } else {
      n->id(closest->size() + 1);
      closest->add_neurite(n);
    }
    return closest;
}
 
std::ostream& operator<<(std::ostream& os, const Reconstruction& r) {
  // Print * line
  os << std::string(50, '*') << std::endl;
  // Print ID:
  os << "Reconstruction ID: " << r.id_ << std::endl;
  // Print Number of neurons
  os << "Neuron count: " << r.neurons_.size() << std::endl;
  // Contour TODO
  /* if (r.has_contour()) {
    os << "Reconstruction contour:" << std::endl;

    for (auto it = r.contour().begin(); it != r.contour().end(); ++it) {
      os << "\t" << boost::format("(%.2f, %.2f, %.2f)") % boost::geometry::get<0>(*it) % boost::geometry::get<1>(*it) %
                        boost::geometry::get<2>(*it) << std::endl;
    }
  } */
  // Print neurons
  if (r.size() > 0) {
    os << "Neurons:" << std::endl << std::endl;
    for (auto it = r.begin(); it != r.end(); ++it) {
      os << *it << std::endl;
    }
  }
  // Print * line
  os << std::string(50, '*') << std::endl;

  return os;
};

}  // End namespace neurostr
