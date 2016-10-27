#include <cctype>

#include "core/contour.h"

namespace neurostr {
  
  
    
    /**
     * @brief Contour empty constructor. Initializes all members to its default value
     * and leaves the contour as empty
    */
    Contour::Contour()
      : name_()
      , positions_()
      , face_color_("#FFFFFF")
      , back_color_("#000000")
      , fill_(0.0)
      , resolution_(1.0)
      , closed_(false){};
    
    /**
     * @brief Creates a contour from a point vector
     * @param v Contour point vector
     */
    Contour::Contour( const std::vector<point_type>& v)
      : name_()
      , positions_(v)
      , face_color_("#FFFFFF")
      , back_color_("#000000")
      , fill_(0.0)
      , resolution_(1.0)
      , closed_(false){};
    
    // Point related functions
    
    Contour::iterator Contour::begin(){ return positions_.begin(); }
    Contour::const_iterator Contour::begin() const { return positions_.begin(); };
    
    Contour::iterator Contour::end() { return positions_.end(); };
    Contour::const_iterator Contour::end() const { return positions_.end(); };
    

    std::size_t Contour::size() const { return positions_.size(); };
    

    float Contour::length() const {
      if(size() <= 1) return 0;
      else {
        float len = 0.0;
        for(auto it = std::next(begin(),1); it != end(); ++it ){
          // Add distance bw every two consecutive points
          len += geometry::distance( *std::prev(it,1), *it);
        }
        // Add one more if it is closed
        if(closed_) {
          len += geometry::distance( *std::prev(end(),1), *begin() );
        }
        return len;
      }
    }
    
    float Contour::area() const {
       if(size() <= 1) return 0;
       else return 0; // TODO: NOT IMPLEMENTED YET
    }
    
    const std::string& Contour::name() const { return name_; }
    

    const std::string& Contour::face_color() const { return face_color_; }
    const std::string& Contour::back_color() const { return back_color_; }
    
    

    float Contour::fill_density() const {return fill_; }

   
    float Contour::resolution() const { return resolution_;}
    
   
    bool Contour::is_closed() const { return closed_;}
    
    
    void Contour::properties_from_map(const PropertyMap& p){
      // Check every property in the map
      for(auto it = p.begin(); it != p.end() ; ++it){
        set_from_property_(*it);
      }
    }
  
  
    bool Contour::float_valued_( const PropertyMap::property_type& p) {
      return PropertyMap::is<float>(p);
    }
    
    bool Contour::string_valued_( const PropertyMap::property_type& p){
      return PropertyMap::is<std::string>(p);  
    }
    
    bool Contour::bool_valued_( const PropertyMap::property_type& p){
      return PropertyMap::is<bool>(p);
    }
    
    bool Contour::check_color_format_(const std::string& s){
      if( s.size()!= 7 ) return false;
      else {
        if( s[0] != '#') return false;
        else {
          for(std::size_t i = 1; i < s.size() ; ++i){
            if( !std::isxdigit(s[i]) ) return false;
          }
          return true;
        }
      }
    }
    
    void Contour::set_from_property_(const PropertyMap::property_type& p){
      
      std::string name = PropertyMap::key(p);
      
      if( name == std::string("back_color") ){
        if( string_valued_(p) )
          back_color_ = PropertyMap::value<std::string>(p);
      } else if( name == std::string("face_color") ){
        if( string_valued_(p) )
          face_color_ = PropertyMap::value<std::string>(p);
      } else if( name == std::string("closed") ){
        if( bool_valued_(p) ){
          closed_ = PropertyMap::value<bool>(p);
          if(closed_ && !(geometry::equal(positions_.front(),positions_.back()))){
            positions_.push_back(positions_.front());
          }
        }
      } else if( name == std::string("filldensity") ){
        if( float_valued_(p) )
          fill_ = PropertyMap::value<float>(p);
      } else if( name == std::string("name") ){
        if( string_valued_(p) )
          name_ = PropertyMap::value<std::string>(p);
      } else if( name == std::string("resolution") ){
        if( float_valued_(p) )
          resolution_ = PropertyMap::value<float>(p);
      }
    }
    
    
    float Contour::closing_gap() const {
      if( closed_ || size() <= 1) {
        return 0.0;
      }
      else {
        return geometry::distance(positions_.front(), positions_.back());
      }
    }
    
    void Contour::close(){
      closed_ = true;
      if(size() > 1){
        if(!(geometry::equal(positions_.front(),positions_.back()))){
              positions_.push_back(positions_.front());
        }
      }
    }
     
    int Contour::planar_axis() const {
      std::pair<float,float> ax_range;
      
      if(size() == 0) return -1;
      else if(size() == 1) return 0;
      
      for(int i = 2 ; i >= 0 ; --i){
        ax_range = range(i);
        if(ax_range.first == ax_range.second ) return i;
      }
      return -1;
    }
     
    std::pair<float,float> Contour::range(int component) const{
      
      if(size() == 0){
        return std::pair<float,float>(0,0);
      }
      
      float min = std::numeric_limits<float>::max();
      float max = std::numeric_limits<float>::min();
      
      for(auto it = begin(); it != end(); ++it ) {
        float v = geometry::get(*it,component);
        if( v < min  ) {
          min = v;
        }
        if( v > max  ) {
          max = v;
        }
      }
      return std::pair<float,float>(min,max);
    }
    
    std::vector<geometry::planar_point> 
    Contour::planar_projection(int component) const{
      // Reserve return
      std::vector<geometry::planar_point> ret;
      ret.reserve(positions_.size());
      
      for(auto it = begin(); it != end() ; ++it){
        ret.push_back(geometry::planar_projection(*it,component));
      }
      return ret;
    }
     
    bool Contour::clockwise_oriented(int i) const{
      
      if(!closed_)
        return false;
        
      // Shoelace formula
      
      // First: get planar projection
      std::vector<geometry::planar_point> planar = planar_projection(i);
      
      // Then compute "area"
      float sum = 0.0;
      for(auto it = std::next(planar.begin(),1); it != planar.end(); ++it){
        auto prev = std::prev(it,1);
          sum+= (geometry::get<0>(*it)-geometry::get<0>(*prev)) *
                (geometry::get<1>(*it)+geometry::get<1>(*prev));
      }
      
      if(closed_){
        sum+=(geometry::get<0>(planar.back())-geometry::get<0>(planar.front())) *
             (geometry::get<1>(planar.back())-geometry::get<1>(planar.front()));
      }
      
      return sum > 0;
    }
     
    void Contour::reverse(){
      std::reverse(positions_.begin(),positions_.end());
    }
     
    void Contour::rotate(iterator new_first){
      if(closed_ && size() > 1 && new_first != end()){
        
        if(new_first == std::prev(positions_.end(),1) )
          new_first = positions_.begin();
          
        // Remove last
        positions_.erase(std::prev(positions_.end(),1));
        std::rotate(positions_.begin(), new_first, positions_.end());
        positions_.push_back(positions_.front());
      }
    }
    
    point_type Contour::barycenter() const{
      if(closed_){
        auto cp = positions_;
        cp.erase(std::prev(cp.end(),1));
        return geometry::barycenter(cp);
      } else {
        return geometry::barycenter(positions_);
      }
      
      
    }


} // end namespace neurostr


