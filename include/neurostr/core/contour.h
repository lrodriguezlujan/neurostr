#ifndef NEUROSTR_BASE_CONTOUR_H_
#define NEUROSTR_BASE_CONTOUR_H_

#include <string>
#include <vector>

#include <neurostr/core/property.h>
#include <neurostr/core/geometry.h>

namespace neurostr {
  
  /**
 * @class Contour
 * @author luis
 * @date 18/10/16
 * @file neuron.h
 * @brief Class that represents a 3D contour in the reconstruction. It is an ordered
 * sequence of 3D points (not nodes). Contours are usually closed but it is not 
 * mandatory.
 * 
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
    
    /**
     * @brief Copy constructor
     */
    Contour(const Contour&) = default;
    
    /**
     * @brief Copy assign
     */
    Contour& operator=(const Contour&) = default;
    
    /**
     * @brief Move constructor
     */
    Contour(Contour&&) = default;
    
    /**
     * @brief Move assign
     */
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
    
    /**
     * @brief Returns an iterator to the first point in the contour
     * @return const point iterator
     */
    const_iterator begin() const;
    
    /**
     * @brief Returns an iterator to the next position after the last 
     * point in the contour
     * @return point iterator
     */
    iterator end();
    
    /**
     * @brief Returns an iterator to the next position after the last 
     * point in the contour
     * @return const point iterator
     */
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
     * @brief Contour planar area as 2D projection in the given component
     * @param component Component that is ignored to compute the area
     * @return Contour planar area
     */
    float area(int component) const;
    
    // Accessors
    
    /**
     * @brief Returns contour name
     * @return Contour name as string
     */
    const std::string& name() const;
    
    /**
     * @brief Set contour name
     * @param n The new contour name
     */
    void name(const std::string& n);
    
    /**
     * @brief Returns contour face color
     * @return Color as hex string #RRGGBB
     */
    const std::string& face_color() const;
    
    /**
     * @brief Returns contour back color
     * @return Color as hex string #RRGGBB
     */
    const std::string& back_color() const;
    
    /**
     * @brief Set contour face color
     * @param s Hex-string color. e.g. #FFFFFF
     */
    void face_color(const std::string& s);
    
    /**
     * @brief Set contour back color
     * @param s Hex-string color. e.g. #FFFFFF
     */
    void back_color(const std::string& s);
    
    /**
     * @brief Return contour fill density (alpha channel)
     * @return Alpha (opacity) value
     */
    float fill_density() const;
    
    /**
     * @brief Set fill density value
     * @param f Contour fill opacity. Between 0 and 1.
     */
    void fill_density(float f);

    /**
     * @brief Contour resolution (im not sure what this actually is..like a ratio?)
     * @return Resolution as float
     */
    float resolution() const;
    
    /**
     * @brief Set resolution value
     * @param f resolution value. Actual meaning is unknown.
     * 
     */
    void resolution(float f);
    
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
    
    /**
     * @brief Distance between the last and the first point in the contour
     * @return Closing gap distance
     */
    float closing_gap() const;
    
    /**
     * @brief Mark the contour as closed (add a segment bw the last and the first)
     */
     void close();
     
     /**
      * @brief Cehcks if the contour is planar for some axis
      * @return -1 is not planar, 0,1,2 x,y,z are constant respectively
      */
     int planar_axis() const;
     
     /**
      * @brief Computes min and max values for the given component (0,1,2 x,y,z)
      * @param component Contour component index (0,1,2 <-> x,y,z)
      * @return Pair (min,max)
      */
      std::pair<float,float> range(int component) const;
      
      /**
       * @brief Returns the contour points removing the ith component
       * @param component Index of component to remove
       * @return Planar points
       */
      std::vector<geometry::planar_point> planar_projection(int component) const;
     
     /**
      * @brief Checks if the contour points are clockwise ordered (shoelace formula applied)
      * @param i component index (0,1,2 <-> x,y,z) that is ignored to compute the orientation
      * @return True if clockwise ordered
      */
     bool clockwise_oriented(int i) const;
     
     /**
      * @brief Reverses the contour point order
      */
     void reverse();
     
     /**
      * @brief Rotates the contour (if it is closed) so the point pointed by new_first
      * becomes the new first point
      * @param new_first Point to become the first point
      */
      void rotate(iterator new_first);
      
      /**
       * @brief Computes contour barycenter
       * @return Barycenter
       */
      point_type barycenter() const;
     
  
  // Private methods
  private:
    
    /**
     * @brief Check the value type of the property
     * @param p Property to check
     * @return true if the property is a float
     */
    static bool float_valued_( const PropertyMap::property_type& p);
    
    /**
     * @brief Check the value type of the property
     * @param p Property to check
     * @return true if the property is a string
     */
    static bool string_valued_( const PropertyMap::property_type& p);
    
    /**
     * @brief Check the value type of the property
     * @param p Property to check
     * @return true if the property is boolean
     */
    static bool bool_valued_( const PropertyMap::property_type& p);
    
    
    /**
     * @brief Verify that the color string is correcty
     * @param s Color string
     * @return true if the color string is an hex color string
     */
    static bool check_color_format_(const std::string& s);
    
    /**
     * @brief Sets a contour value from a single property (by name)
     * @param p Property to evaluate
     */
    void set_from_property_(const PropertyMap::property_type& p);

}; // End class contour

} // end namespace neurostr



#endif
