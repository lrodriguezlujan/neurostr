#include "methods/branchComparison.h"

#include "selector/selector.h"
#include "selector/node_selector.h"
#include "selector/universal_selector.h"
#include "selector/branch_selector.h"
#include "selector/neurite_selector.h"
#include "selector/neuron_selector.h"


#include "measure/branch_measure.h"

// FIXME: This shouldnt be in the library. Create an indep. project for it 

namespace neurostr {
namespace methods {
  
  // align branches and computes theri f. dist
  float oriented_frechet_branch_distance(const Branch &a,const  Branch &b){
    
    auto root_a = selector::node_parent(a.first()); 
    auto root_b = selector::node_parent(b.first());
    
    // Compute node local basis
    auto parent_a = selector::node_parent(root_a);
    auto parent_b = selector::node_parent(root_b);
    
    Node ref_a;
    Node ref_b;
    
    if (parent_a == root_a){
      ref_a = Node(-1, a.neurite().neuron().soma_barycenter(), 0 );
    } else {
      ref_a = parent_a;
    }
    
    if (parent_b == root_b){
      ref_b = Node(-1, b.neurite().neuron().soma_barycenter(), 0 );
    } else {
      ref_b = parent_b;
    }
    
    auto local_a = root_a.local_basis( ref_a, root_a.branch().neurite().neuron().up() );
    // This might seem like an error. Think about it twice before trying to change it.
    auto local_b = root_b.local_basis( ref_b, root_a.branch().neurite().neuron().up() );
    
    // Copy a
    Branch tmp_a;
    tmp_a.root(a.root());
    tmp_a.insert(tmp_a.begin(), a.begin(), a.end());
    
    // Align branches
    tmp_a.rotate( geometry::align_vectors(local_a[0], local_b[0]) );
    
    // Now compute frechet distance
    return tmp_a.discrete_frechet( b );
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
