#ifndef NEUROSTR_METHODS_SCHOLL_H_
#define NEUROSTR_METHODS_SCHOLL_H_

#include <vector>
#include <array>

#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"
#include "methods/boxCutter.h"

#include "measure/measure.h"
#include "measure/node_measure.h"
#include "measure/universal_measure.h"
#include "measure/aggregate.h"

#include "selector/selector.h"
#include "selector/node_selector.h"
#include "selector/universal_selector.h"



namespace neurostr{
namespace methods{

  // Kind of 2-col matrix return

std::vector<std::pair<float, int>> schollAnalysis(Neuron& n);
//std::vector<std::array<float,2>> exactSchollAnalysis(Neuron& n);
  
template <geometry::Axis axis>
std::vector<std::array<float,2>> boxcutSchollAnalysis(Neuron& n, float start = 0.1, float end = 1, float inc = 0.01){
    
    using retType = std::vector<std::array<float,2>>;
    retType::size_type elements = std::ceil((end-start)/inc);
    
    // We know its size beforehand
    std::vector<std::array<float,2>> ret(elements+1);
    
    // Center
    n.center();
    
    // Compute axis length
    auto bbox = n.boundingBox();
    float len = geometry::axisLength<axis>(bbox);
    
    // Cut node selector
    auto cutsel = selector::compose_selector(selector::property_exists_factory<Node>("cut"),
                                             selector::neuron_node_selector);
                                                            
    // Total length measure
    auto total_len = measure::measureEachAggregate(measure::node_length_to_parent,
                                                   measure::aggregate::sum_aggr_factory<float>(0.));
    // All nodes
    auto total_sel = neurostr::selector::neuron_node_selector(n);
    
    float neuron_length = total_len(total_sel.begin(),total_sel.end());
    
    // Compute
    float tempLen;
    for(retType::size_type i = 0; i <= elements ; ++i){
        // compute length for this run
        tempLen = len * (start + (i * inc));
        
        // Change bbox
        geometry::setAxis<axis>(bbox, tempLen );
        
        // Cut
        methods::neuronBoxCutter(n,bbox.min_corner(),bbox.max_corner());
        
        // Select and measure
        auto sel = cutsel(n);
        float len_var = sel.size()==0?0.:total_len(sel.begin(),sel.end());
        
        // Add
        ret[i] = {start + (i*inc), len_var/neuron_length};

        methods::BoxCutterRestore(n);
    }
    return ret;
};



    
} // methods
} // neurostr



#endif
