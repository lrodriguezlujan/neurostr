#ifndef NEUROSTR_BASE_CONTOUR_H_
#define NEUROSTR_BASE_CONTOUR_H_

#include <string>
#include <vector>

#include "core/property.h"
#include "core/geometry.h"

namespace neurostr {
  
  /**
 * @class Contour
 * @author luis
 * @date 18/10/16
 * @file neuron.h
 * @brief 
 */
class Contour{
  
  // Constructors
  public:
  
    // convenience typedefs
    using storage_type = std::vector<point_type>;
    using iterator = storage_type::iterator;
    using const_iterator = storage_type::const_iterator;
    
    /**
     * @brief Contour empty constructor. Initializes all members to its default value
     * and leaves the contour as empty
    */
    Contour();
    
    /**
     * @brief Creates a contour from a point vector
     * @param v Contour point vector
     */
    Contour( const std::vector<point_type>& v);
    
    // copy and move
    Contour(const Contour&) = default;
    Contour& operator=(const Contour&) = default;
    
    Contour(Contour&&) = default;
    Contour& operator=(Contour&&) = default;
  
  // Data members
  private: 
  
    // Contour name
    std::string name_;
    
    // Points
    std::vector<point_type> positions_;
    
    // Colors
    std::string face_color_;
    std::string back_color_;
    float fill_;
    
    // Resolution
    float resolution_;
    
    // Closed contour flag
    bool closed_;
  
  // Member functions
  public:
    
    // Point related functions
    
    /**
     * @brief Returns an iterator to the first point in the contour
     * @return point iterator
     */
    iterator begin();
    const_iterator begin() const;
    
    /**
     * @brief Returns an iterator to the next position after the last 
     * point in the contour
     * @return point iterator
     */
    iterator end();
    const_iterator end() const;
    
    
    /**
     * @brief Contour size
     * @return number of points that describe the contour
     */
    std::size_t size() const;
    
    /**
     * @brief Computes the length of the contour
     * @return Contour length
     */
    float length() const;
    
    /**
     * @brief Contour planar area as 2D projection
     * @return Contour planar area
     */
    float area() const;
    
    // Accessors
    
    /**
     * @brief Returns contour name
     * @return Contour name as string
     */
    const std::string& name() const;
    
    /**
     * @brief Returns contour face and back color
     * @return Color as hex string #RRGGBB
     */
    const std::string& face_color() const;
    const std::string& back_color() const;
    
    
    /**
     * @brief Return contour fill density (alpha channel)
     * @return Alpha (opacity) value
     */
    float fill_density() const;

    /**
     * @brief Contour resolution (im not sure what this actually is..like a ratio?)
     * @return Resolution as float
     */
    float resolution() const;
    
    /**
     * @brief True if the contour is defined as closed
     * @return boolean flag
     */
    bool is_closed() const;
    
    /**
     * @brief Set all contour properties getting them from a p. map
     * @param p input Property map
     */
    void properties_from_map(const PropertyMap& p);
  
  // Private methods
  private:
    
    /**
     * @brief Check the value type of the property
     * @param p Property to check
     */
    static bool float_valued_( const PropertyMap::property_type& p);
    static bool string_valued_( const PropertyMap::property_type& p);
    static bool bool_valued_( const PropertyMap::property_type& p);
    
    
    /**
     * @brief Verify that the color string is correcty
     * @param s Color string
     */
    static bool check_color_format_(const std::string& s);
    
    void set_from_property_(const PropertyMap::property_type& p);

}; // End class contour

} // end namespace neurostr



#endif
