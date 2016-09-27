#include "core/branch.h"
#include "core/geometry.h"
#include <iostream>
#include <ios>

namespace neurostr{
 
/******
 * 
 * BRANCH METHODS
 * 
 */
 
 std::string Branch::idString() const {
   std::string ret = std::to_string(*(id_.begin()));
   for( auto it = ++id_.begin(); it != id_.end() ; it++ ){
     ret += std::string("-") + std::to_string(*it);
   }
   return ret;
 }
 
// Friend output method
std::ostream& operator<<(std::ostream& os, const Branch& b){
  std::string padding(b.order()+1, os.fill() );
  
  os << padding << "Branch ";
  
  // Print id
  os << *b.id().begin();
  for( auto it = ++b.id().cbegin(); it != b.id().cend() ; it++ )
    os << "-" << *it;
  os << std::endl;
  // Print order
  os << padding << "\t order: " << b.order() << std::endl;
  
    // Print root
  if(b.has_root())
    os << padding  << "\t root: " << b.root() << std::endl;
  else
    os << padding  << "\t NO ROOT DEFINED" << std::endl;
  
  // Print number of nodes
  os << padding << "\t# nodes: " << b.size() << std::endl;
  
  // Print content
  for( auto it = b.cbegin(); it != b.cend() ; it++ )
    os << padding  << "\t" << *it << std::endl;
    
  return os;
};

  // Erase
  Branch::iterator Branch::erase(const Branch::iterator& pos) { 
    
    if(pos == end()) return pos;
    
    auto next = std::next(pos,1);
    if( next != end() ){
      next->invalidate_basis();
      next->invalidate_length();
      next->parent(&(pos->parent()));
    }
    return nodes_.erase(pos.base());
  }
  Branch::iterator Branch::erase(const Branch::iterator& first,
                                 const Branch::iterator& last) { 
    if( last != end() ){
      last->invalidate_basis();
      last->invalidate_length();
    }
    
    return nodes_.erase(first.base(), last.base());
  }
  
  // Transformations
  void Branch::simplify(float eps){
    
    if(size() == 1) {
      return;
      
    } else if(eps < 0) {
      eps = (-eps) * (root_->radius() + last().radius() ) / 2.0 ;
    }
    
    std::vector<Node> tmp;
    
    // Add root
    tmp.push_back(*root_);
    
    // Add nodes
    tmp.insert(tmp.end(), begin(), end() );
    
    // RDP Simplification
    geometry::RDPSimplifier<Node>(eps,tmp).simplify();
    
    // Remove nodes
    auto ref = begin();
    for(auto it = std::next(tmp.begin(),1); it != tmp.end(); ++it){
      while(*ref != *it){
        ref = erase(ref);
      }
      
      if (ref != end()){
        ++ref;
      }
    }
    
  }
  
  void Branch::scale(float r){
    
    // First node scales wrt to root...if it exists
    if ( has_root() ){
      begin()->scale(r,root().position()) ;
    } else {
      begin()->scale(r,point_type(0,0,0)) ;
    }
      
    for(auto it  = std::next(begin(),1); it != end() ; ++it){
      it->scale(r,(it-1)->position());
    }
  }
  
  void Branch::scale(float rx, float ry, float rz){
    // First node scales wrt to root...if it exists
    if ( has_root() ) root_->scale(rx,ry,rz);
  
    for(auto it  = begin(); it != end() ; ++it){
      it->scale(rx,ry,rz);
    }
  }
  
  void Branch::traslate(const point_type& p){
      
    for(auto it  = begin(); it != end() ; ++it){
      it->traslate(p);
    }
      
    // Move also the root
    if ( has_root() ) {
      root_->traslate(p);
    }
  }
  
  void Branch::rotate(const Eigen::Quaternionf& q){
    for(auto it  = begin(); it != end() ; ++it){
      it->rotate(q);
    }
      
      // Move also the root
    if ( has_root() ) {
      root_->rotate(q);
    }
  }
  
  void Branch::remove_null_segments(){
    // Check if we should remove the first node
    if( has_root() ){
      // Do it ...
      while(geometry::equal(begin()->position(), root_->position()) && nodes_.size() > 0){
        erase(begin());
      }
    }
    if(size() > 0)
      for(auto it = std::next(begin(),1) ; it != end(); ++it){
        if ( geometry::equal( std::prev(it,1)->position(), it->position()) ){
          it = erase(it);
          --it;
        }
      }
  }
  
  float Branch::discrete_frechet(const Branch& other) const {
    
    using iter_type = std::vector<point_type>::const_iterator;
    
    // Create point_type vectors to include root
    std::vector<point_type> a(size()+1);
    std::vector<point_type> b(other.size()+1);
    
    // Add roots
    a.push_back(root().position());
    b.push_back(other.root().position());
    
    // Add nodes
    for(auto it = begin(); it != end() ; ++it ){
      a.push_back(it->position());
    }
    
    for(auto it = other.begin(); it != other.end() ; ++it ){
      b.push_back(it->position());
    }
    
    // Compute discrete frechet
    return geometry::DiscreteFrechet<iter_type,iter_type>(a.begin(),
                                                          a.end(),
                                                          b.begin(),
                                                          b.end()).value();
  }

      
} // Namespace neurostr
