#ifndef NEUROSTR_MEASURE_AGGREGATOR_FUNCS_H_
#define NEUROSTR_MEASURE_AGGREGATOR_FUNCS_H_

#include<algorithm>
#include<numeric>
#include<array>
#include<iostream>

namespace neurostr {
namespace measure {
namespace aggregate {
  
namespace detail {
  
  template <typename T>
  using iterator_type = typename std::vector<T>::iterator;
  
} // DEtail ns

template <typename U , typename T = U>
struct aggr_pack{
  aggr_pack( U sum_, U min_, U max_, U median_, T mean_, T sd_) 
    : sum(sum_)
    , min(min_)
    , max(max_)
    , median(median_)
    , mean(mean_)
    , sd(sd_){};
  
  U sum;
  U min;
  U max;
  U median;
  T mean;
  T sd;
};




template <typename U, typename T = U>
const auto sum_aggr_factory(T zero){
  return [z_ = zero](const detail::iterator_type<U>& b, 
                     const detail::iterator_type<U>& e) -> T {
    return static_cast<T>(std::accumulate(b,e,z_));
  };
}

template <typename U, typename T = U>
const auto avg_aggr_factory(T zero){
  return [z_ = zero](const detail::iterator_type<U>& b, 
                     const detail::iterator_type<U>& e) -> T {
    if(b == e) return std::numeric_limits<T>::infinity();
    auto dist = std::distance(b,e);
    return static_cast<T>(std::accumulate(b,e,z_))/dist;
  };
}

template <typename U, typename T = U>
const auto mean_sd_factory(T zero){
  return [z_ = zero](const detail::iterator_type<U>& b, 
                     const detail::iterator_type<U>& e) -> std::array<T,2> {
    auto size = std::distance(b,e);
    T mean = std::accumulate(b,e,z_);
    mean/=size;
    
    std::vector<T> diff(size);
    std::transform(b, e, diff.begin(), [m_=mean](double x) { return x - m_; });
    T sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), z_);
    
    
    std::array<T,2> ret{ {mean,std::sqrt(sq_sum / (size-1))} };
    return ret;
  };
};

template <typename U = float, typename T = U>
const auto max = [](const detail::iterator_type<U>& b, 
              const detail::iterator_type<U>& e) -> T {
  if(b == e) return std::numeric_limits<T>::infinity();
     return static_cast<T>(*std::max_element(b,e));
};
  
template <typename U = float, typename T = U>
const auto min = [](const detail::iterator_type<U>& b, 
              const detail::iterator_type<U>& e) -> T {
  if(b == e) return std::numeric_limits<T>::infinity();
    return static_cast<T>(*std::min_element(b,e));
};
  
template <typename U = float, typename T = U>
const auto median = [](const detail::iterator_type<U>& b, 
                 const detail::iterator_type<U>& e) -> T {
     if(b == e) return std::numeric_limits<T>::infinity();
    
    // Copy values
    std::vector<U> tmp(b,e);
    auto n = tmp.size() / 2;
    
    //Comput nth elements
    std::nth_element(tmp.begin(),tmp.begin()+n,tmp.end());
    if( (tmp.size() % 2 ) == 0) {
      // Even case
      std::nth_element(tmp.begin(),tmp.begin()+n+1,tmp.end());
      return static_cast<T>((tmp[n] + tmp[n + 1]) / 2);
    } else
      return static_cast<T>(tmp[n]);
};

template <typename T>
auto range_length = [](const detail::iterator_type<T>& b, 
                       const detail::iterator_type<T>& e) -> T {
            T min_ = min<T,T>(b,e);
            T max_ = max<T,T>(b,e);
            return max_-min_;
};

template <typename U = float, typename T = U>
const auto all_aggr_factory(T zero){
  return [z_ = zero](const detail::iterator_type<U>& b, 
                     const detail::iterator_type<U>& e) -> aggr_pack<U,T> {
    auto tmp = mean_sd_factory<U,T>(z_)(b,e);
    
    return aggr_pack<U,T>(sum_aggr_factory<U,T>(z_)(b,e),
            min<U,T>(b,e),
            max<U,T>(b,e),
            median<U,T>(b,e),
            tmp[0],
            tmp[1]);
  };
};
  
} // Aggreg
}  // measures
}  // neurostr

template <typename U , typename T = U>
std::ostream& operator<<(std::ostream& s, const neurostr::measure::aggregate::aggr_pack<U,T>& v){
  s << v.sum << ", " << v.min << ", " << v.max 
    << ", " << v.median <<  ", " << v.mean <<  ", " << v.sd;
  return s;
};



#endif
