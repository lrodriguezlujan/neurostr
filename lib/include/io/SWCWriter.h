#ifndef NEUROSTRLIB_IO_SWCWRITER_H_
#define NEUROSTRLIB_IO_SWCWRITER_H_

#include <iostream>
#include <string>
#include <boost/format.hpp>

#include "core/property.h"
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neurite_type.h"
#include "core/neuron.h"

#include "selector/node_selector.h"

namespace neurostr {
namespace io {
  
  class SWCWriter {
    
    public: 
      const char comment_char = '#';
      const int  no_parent_id = -1;
      
      SWCWriter(std::ostream&);
      ~SWCWriter();
      
      std::ostream& write(Neuron&) const;
      
      
      static unsigned int convertNeuriteType(const NeuriteType&);
    
    protected:
      
      void writeHeader(Neuron&) const ;
      void writeData(Neuron&) const ;
      
    private:
      // Header 
      void writeStaticHeader() const ;
      void writeNeuroInfo(Neuron&) const ;
      void writeNeuroProperties(Neuron&) const ;
      void writeProperty(const PropertyMap::property_type&) const ;
      
      // Data 
      void writeNode(Node&, unsigned int type, int parent) const ;
    
    
      std::ostream& stream_;
    
  };
  
  
} // io
} // neurostr

#endif
