#include <neurostr/methods/branchComparison.h>

// FIXME: This shouldnt be in the library. Create an indep. project for it 

namespace neurostr {
namespace methods {
  
  // align branches and computes theri f. dist
  float oriented_frechet_branch_distance(const Branch &a,const  Branch &b, bool normalize){
    
    Node root_a, root_b;
    
    // Copy
    Branch tmp_a,tmp_b;
    if(a.has_root()){
      tmp_a.root(a.root());
    }
    tmp_a.insert(tmp_a.begin(), a.begin(), a.end());
    
    if(b.has_root()){
      tmp_b.root(b.root());
    }
    tmp_b.insert(tmp_b.begin(), b.begin(), b.end());
    
    // normalize
    if( normalize ){
      tmp_a.normalize();
      tmp_b.normalize();
    }
    
    // No alignment needed
    if(tmp_a.size() == 0 || tmp_b.size() == 0) {
      return(tmp_a.discrete_frechet(tmp_b));
    }
    
    // Get roots
    if(tmp_a.has_root()) { root_a = tmp_a.root(); }
    else { root_a = tmp_a.first();}
    
    if(tmp_b.has_root()) { root_b = tmp_b.root(); }
    else { root_b = tmp_b.first();}
    
    // Compute node local basis
    point_type ref_a = root_a.vectorTo(tmp_a.last());
    point_type ref_b = root_b.vectorTo(tmp_b.last());
    
    // If any ref is 0 -> no alignment
    if(geometry::norm(ref_a) == 0 || geometry::norm(ref_b) == 0){
      return(tmp_a.discrete_frechet(tmp_b));
    }
    
    // Align branches
    tmp_a.rotate( geometry::align_vectors(ref_a, ref_b) );
    if(tmp_a.has_root()) { tmp_a.traslate(tmp_a.root().vectorTo(root_b)); }
    else { tmp_a.traslate(tmp_a.first().vectorTo(root_b)); }
    
    
    
    // Now compute frechet distance
    return tmp_a.discrete_frechet( tmp_b );
  }
  
  std::vector<float> inter_pair_distance(const  Neuron& n, bool restrict_order, bool sided ){
  
    auto v = selector::compose_selector(
              selector::selector_in_single_to_set(selector::neurite_branch_selector), 
              selector::neuron_neurites)(n);
              
    std::vector<float> distances( ( v.size() * (v.size()-1) ) / 2 ); // Biggest size possible
    
    std::vector<float>::size_type pos = 0;
    if(!restrict_order){
      for(auto i = v.begin(); i != --v.end(); ++i ){
        for(auto j = i+1 ; j != v.end(); ++j){
          distances[pos++] = oriented_frechet_branch_distance(i->get(),j->get());
        }
      }
    } else {
      
      int maxOrder = 0;
      for( auto it = n.begin_neurite(); it != n.end_neurite(); ++it )
        if(it->max_centrifugal_order() > maxOrder) maxOrder = it->max_centrifugal_order();
      
      // Compute for each order
      std::vector<selector::const_branch_reference> tmp;
      
      for(int i = 0; i<= maxOrder ; ++i ){
        // Filter references
        tmp = selector::branch_order_filter_factory(i)(v.begin(),v.end()); 
        for(auto j = tmp.begin(); j != --tmp.end(); ++j ){
          for(auto k = j+1 ; k != tmp.end(); ++k){
            if( i != 0 && sided ){
              // Get "J" positions (0 left, 1 right) if they match. compute distance
              if( measure::branch_index(j->get()) == measure::branch_index(k->get()) ){
                    distances[pos++] = oriented_frechet_branch_distance(j->get(),k->get()); 
              }
            }
            else {
              distances[pos++] = oriented_frechet_branch_distance(j->get(),k->get());  
            }
            
          }
        }
      }
      distances.resize(pos);
    }
    return distances;
  }
  
  std::vector<std::vector<float>> inter_pair_distance_byorder(const Neuron& n, bool sided){
  
    auto v = selector::compose_selector(
              selector::selector_in_single_to_set(selector::neurite_branch_selector), 
              selector::neuron_neurites)(n);
    
    int maxOrder = 0;
    for( auto it = n.begin_neurite(); it != n.end_neurite(); ++it )
      if(it->max_centrifugal_order() > maxOrder) maxOrder = it->max_centrifugal_order();
    
    std::vector<std::vector<float>> distances(maxOrder+1);
    
    // Compute for each order
    std::vector<selector::const_branch_reference> tmp;
      
    for(int i = 0; i<= maxOrder ; ++i ){
        distances[i] = std::vector<float>();
        // Filter references
        tmp = selector::branch_order_filter_factory(i)(v.begin(),v.end()); 
        for(auto j = tmp.begin(); j != --tmp.end(); ++j ){
          for(auto k = j+1 ; k != tmp.end(); ++k){
            if( i != 0 && sided ){
              // Get "J" positions (0 left, 1 right) if they match. compute distance
              if( measure::branch_index(j->get()) == measure::branch_index(k->get()) ){
                    distances[i].push_back(oriented_frechet_branch_distance(j->get(), k->get())); 
              }
            }
            else {
              distances[i].push_back(oriented_frechet_branch_distance(j->get(),k->get()));  
            }
            
          }
        }
    }
    return distances;
  }
  
} // Selector
} // Neurostr
