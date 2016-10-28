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
  
  /**
   * @class SWCWriter
   * @author luis
   * @date 28/10/16
   * @file SWCWriter.h
   * @brief Writes a reconstruction in standard SWC format
   */
  class SWCWriter {
    
    public: 
      //  Comments (for properties)
      const char comment_char = '#';
      // Parent for orphan nodes
      const int  no_parent_id = -1;
      
      /**
       * @brief Creates a writer over the given stream
       * @return SWCWriter
       */
      SWCWriter(std::ostream&);
      ~SWCWriter();
      
      /**
       * @brief Writes the given neuron in SWC format
       * @return Output stream reference
       */
      std::ostream& write(Neuron&) const;
      
      /**
       * @brief Auxiliar function that converts the neurite type into
       * SWC defined types
       * @return SWC int type
       */
      static unsigned int convertNeuriteType(const NeuriteType&);
    
    protected:
      
      /**
       * @brief Writes document header. Static header + properties
       * as comments
       */
      void writeHeader(Neuron&) const ;
      
      /**
       * @brief Writes Neuron node positions (SWC DATA)
       */
      void writeData(Neuron&) const ;
      
    private:
      
      /**
       * @brief Writes a static header as a comment in the SWC file
       */
      void writeStaticHeader() const ;
      
      /**
       * @brief Writes basic neuron info (name...) as comments in the file
       */
      void writeNeuroInfo(Neuron&) const ;
      
      /**
       * @brief Writes neuron properties as comments in the SWC file
       */
      void writeNeuroProperties(Neuron&) const ;
      
      /**
       * @brief Writes a property as # propname propvalue string
       */
      void writeProperty(const PropertyMap::property_type&) const ;
      
      /**
       * @brief Writes a node in the SWC file
       * @param n Node
       * @param type SWC numeric type
       * @param parent Parent id (-1 if its an orphan node)
       */
      void writeNode(Node& n, unsigned int type, int parent) const ;
    
    
      std::ostream& stream_;
    
  };
  
  
} // io
} // neurostr

#endif
