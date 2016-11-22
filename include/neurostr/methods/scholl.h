#ifndef NEUROSTR_METHODS_SCHOLL_H_
#define NEUROSTR_METHODS_SCHOLL_H_

#include <vector>
#include <array>

#include <neurostr/core/node.h>
#include <neurostr/core/branch.h>
#include <neurostr/core/neurite.h>
#include <neurostr/core/neuron.h>
#include <neurostr/methods/boxCutter.h>

#include <neurostr/measure/measure.h>
#include <neurostr/measure/node_measure.h>
#include <neurostr/measure/universal_measure.h>
#include <neurostr/measure/aggregate.h>
#include <neurostr/measure/neurite_measure.h>

#include <neurostr/selector/selector.h>
#include <neurostr/selector/node_selector.h>
#include <neurostr/selector/universal_selector.h>





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
