#include <map>
#include <list>
#include <memory>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <cstddef>
#include <utility>
#include <fstream>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <type_traits>

#include "core/neuron.h"
#include "io/parser_dispatcher.h"
#include "validator/validator.h"
#include "validator/predefined_validators.h"
#include "measure/lmeasure_decl.h"

using Neuron = neurostr::Neuron;

namespace bmk
{

  using std::map; 
	using std::pair;
	using std::vector; 
	using std::string;
	using std::size_t; 
	using std::ostream; 
	using std::is_same; 
	using std::forward; 
	using std::ofstream; 
	using std::enable_if; 
	using std::unique_ptr; 
	using std::result_of_t; 
	using std::make_unique; 
	using std::initializer_list; 
	using std::remove_reference; 
	using std::integral_constant;
	using std::chrono::time_point; 
	using std::chrono::duration_cast; 

	/// folly function to avoid optimizing code away 
#ifdef _MSC_VER
	#pragma optimize("", off)
	template <class T>
	void doNotOptimizeAway(T&& datum) 
	{
		datum = datum;
	}
	#pragma optimize("", on)
#else
	template <class T>
	void doNotOptimizeAway(T&& datum) 
	{
		asm volatile("" : "+r" (datum));
	}
#endif

// calculate the mean value
template<typename C>
auto mean(C&& data)
{
	return std::accumulate(begin(data), end(data),
	(std::remove_reference_t<decltype(*begin(data))>)0) / data.size();
}

/// get the name of the chrono time type string
template<typename T> string time_type()                            { return "unknown";      }
template<          > string time_type<std::chrono::nanoseconds >() { return "nanoseconds";  }
template<          > string time_type<std::chrono::microseconds>() { return "microseconds"; }
template<          > string time_type<std::chrono::milliseconds>() { return "milliseconds"; }
template<          > string time_type<std::chrono::seconds     >() { return "seconds";      }
template<          > string time_type<std::chrono::minutes     >() { return "minutes";      }
template<          > string time_type<std::chrono::hours       >() { return "hours";        }

template<class TimeT=std::chrono::milliseconds, class ClockT=std::chrono::steady_clock>
class timeout {

  TimeT _total{ 0 };
	decltype(ClockT::now()) _start;
	public:
	void tic(){
    _start = ClockT::now();
  }
	
  void toc(){
    _total += duration_cast<TimeT>(ClockT::now() - _start);
  }
	
  TimeT duration() const{
    return _total;
  }
};

template<class TimeT = std::chrono::milliseconds, class ClockT = std::chrono::steady_clock>
using timeout_ptr = unique_ptr < timeout < TimeT, ClockT > > ; 

namespace detail{
/**
* @class experiment_impl
* @brief implementation details of an experiment
*/
template<class TimeT, class FactorT>
struct experiment_impl {
  string                      _fctName; 
	map<FactorT, vector<TimeT>> _timings;
	
	experiment_impl(string const& factorName)
    : _fctName(factorName)
		{ }

  // implementation of forwarded functions --------------------
	void print(ostream& os) const {
    string token{ "" }; 

		os << ", 'factor_name' : '" << _fctName << "'"; 
		// print the factor list
		os << ", 'factors' : [ "; 
		for (auto&& Pair : _timings) {
      os << token; 
			os << Pair.first; 
			token = ", "; 
    }
		os << " ]"; 
		// print the timings
		token.clear(); 
		os << ", 'timings' : [ ";
		for (auto&& Pair : _timings){
      os << token; 
			os << mean(Pair.second).count();
			token = ", ";
    }
		os << " ]";
  }
protected:
			~experiment_impl() = default; 
};

template<class TimeT>
struct experiment_impl < TimeT, void >
{
	vector<TimeT> _timings;

	experiment_impl(size_t nSample)
		: _timings(nSample)	{ }
			
  // implementation of forwarded functions --------------------
	void print(ostream& os) const
	{
		string token{ "" };
		// print the timings
		os << ", 'timings' : [ ";
		for (auto&& elem : _timings)
		{
			os << token;
			os << elem.count();
			token = ", ";
		}
		os << " ]";
	}

	protected:
	~experiment_impl() = default;
};

/**
* @ class experiment
* @ brief base class to serve as an experiment concept
*/
struct experiment
{
	virtual ~experiment()
	{ }

	// forwarded functions --------------------------------------
	virtual void print(ostream& os) const = 0;
};

template<class TimeT, class ClockT>
struct measure
{
	template<class F>
  inline static auto duration(F callable)
		-> typename enable_if < !is_same <
		decltype(callable()), timeout_ptr<TimeT, ClockT>>::value, TimeT > ::type
	{
		auto start = ClockT::now();
		callable();
		return duration_cast<TimeT>(ClockT::now() - start);
	}
		template<class F>
	inline static auto duration(F callable)
		-> typename enable_if < is_same < 
		decltype(callable()), timeout_ptr<TimeT, ClockT> >::value, TimeT > ::type
	{
		auto start = ClockT::now();
		auto tOut  = callable();
		return (duration_cast<TimeT>(ClockT::now() - start)) - tOut->duration();
	}

	template<class F, typename FactorT>
	inline static auto duration(F callable, FactorT&& factor)
		-> typename enable_if < !is_same < 
		decltype(callable(forward<FactorT>(factor))), timeout_ptr<TimeT, ClockT>
		>::value, TimeT >::type
	{

		auto start = ClockT::now();
		callable(forward<FactorT>(factor));
		return duration_cast<TimeT>(ClockT::now() - start);
	}

			template<class F, typename FactorT>
			inline static auto duration(F callable, FactorT&& factor)
				-> typename enable_if < is_same < 
				decltype(callable(forward<FactorT>(factor))), timeout_ptr<TimeT, ClockT>
				>::value, TimeT >::type
			{
				auto start = ClockT::now();
				auto tOut  = callable(forward<FactorT>(factor));
				return (duration_cast<TimeT>(ClockT::now() - start)) - tOut->duration();
			}
		};

		/**
		* @ class experiment_model
		* @ brief abrastraction for a single sampling process
		*/
		template <
			class TimeT, class ClockT, class FactorT = void
		>
		struct experiment_model final
			: experiment
			, experiment_impl < TimeT, FactorT >
		{
			// construction - destruction -------------------------------
			template<class F>
			experiment_model(size_t nSample, F callable)
				: experiment_impl<TimeT, void>(nSample)
			{
				for (size_t i = 0; i < nSample; i++)
				{
					experiment_impl<TimeT, FactorT>::_timings[i] = measure<TimeT, ClockT>
						::duration(callable);
				}
			}

			template<class F>
			experiment_model(
				size_t nSample, F callable, 
				string const& factorName, initializer_list<FactorT>&& factors)
				: experiment_impl<TimeT, FactorT>(factorName)
			{
				for (auto&& factor : factors)
				{
					experiment_impl<TimeT, FactorT>::_timings[factor].reserve(nSample);
					for (size_t i = 0; i < nSample; i++)
					{
						experiment_impl<TimeT, FactorT>::_timings[factor].push_back(
							measure<TimeT, ClockT>::duration(callable, factor));
					}
				}
			}

			template<class F, class It>
			experiment_model(size_t nSample, F callable, string const& factorName, It beg, It fin)
				: experiment_impl<
					TimeT, typename remove_reference<decltype(*beg)>::type>(factorName)
			{
				while (beg != fin)
				{
					experiment_impl<TimeT, FactorT>::_timings[*beg].reserve(nSample);
					for (size_t i = 0; i < nSample; i++)
					{
						experiment_impl<TimeT, FactorT>::_timings[*beg].push_back(
							measure<TimeT, ClockT>::duration(callable, *beg));
					}
					++beg;
				}
			}

			// forwarded functions --------------------------------------
			void print(ostream& os) const override
			{
				experiment_impl<TimeT, FactorT>::print(os);
			}

		};
	} // ~ namespace detail

	/**
	* @ class benchmark
	* @ brief organizes the execution and serialization of timing experiments
	*/
	template <
		typename TimeT = std::chrono::milliseconds, class ClockT = std::chrono::steady_clock
	>
	class benchmark
	{
		vector<pair<string, unique_ptr<detail::experiment>>> _data; 

	public:
		// construction - destruction -----------------------------------
		benchmark()                 = default; 
		benchmark(benchmark const&) = delete; 

		// run experiments ----------------------------------------------
		template<class F>
		void run(string const& name, size_t nSample, F callable)
		{
			_data.emplace_back(name, make_unique< 
				detail::experiment_model<TimeT, ClockT>>(nSample, callable));
		}

		template<class FactorT, class F>
		void run(
			string const& name, size_t nSample, F callable, 
			string const& factorName, initializer_list<FactorT>&& factors)
		{
			_data.emplace_back(name, make_unique<detail::experiment_model<TimeT, ClockT, FactorT>>(
				nSample, callable, factorName, forward<initializer_list<FactorT>&&>(factors)));
		}

		template<class F, class It>
		void run(
			string const& name, size_t nSample, 
			F callable, string const& factorName, It beg, It fin)
		{
			_data.emplace_back(name, make_unique<detail::experiment_model<TimeT, ClockT,
				typename remove_reference<decltype(*beg)>::type>>(
				nSample, callable, factorName, beg, fin));
		}

		// utilities ----------------------------------------------------
		void print(const char* benchmarkName, ostream& os) const
		{
			for (auto&& Pair : _data)
			{
				os << "{ 'benchmark_name' : '" << benchmarkName << "'";
				os << ", 'experiment_name' : '" << Pair.first << "'";
				os << ", 'time_type' : '" << time_type<TimeT>() << "'";
				Pair.second->print(os);
				os << " } \n";
			}
		}

		void serialize(
			const char* benchmarkName, const char *filename,
			std::ios_base::openmode mode = ofstream::out) const
		{
			ofstream os;
			os.open(filename, mode);
			for (auto&& Pair : _data)
			{
				os << "{ 'benchmark_name' : '" << benchmarkName << "'";
				os << ", 'experiment_name' : '" << Pair.first << "'";
				os << ", 'time_type' : '" << time_type<TimeT>() << "'";
				Pair.second->print(os);
				os << " } \n";
			}
			os.close(); 
		}
	};

} // ~ namespace bmk


/**** PROGRAM STARTS HERE! */
const std::string dat_small = "../data/A9-7.DAT";
const std::string dat_med = "../data/RC6-P1F6C4LVc-cs-Sh.DAT";
const std::string dat_large = "../data/A090622.DAT";

const std::string asc_small = "../data/02b_pyramidal1aACC.ASC";
const std::string asc_med = "../data/CzI_2.asc";
const std::string asc_large = "../data/VPM_1.asc";

const std::string swc_small = "../data/A9-7.CNG.swc";
const std::string swc_med = "../data/cZI_2.CNG.swc";
const std::string swc_large = "../data/VPM_1.CNG.swc";

const std::string json_small = "../data/A9-7.json";
const std::string json_med = "../data/cZI_2.json";
const std::string json_large = "../data/VPM_1.json";

// READ SPPED TEST
const auto load_file_test = [](const std::string& path){
  // Read reconstruction
  auto  r = neurostr::io::read_file_by_ext(path);
  // ...aaaand thats it
};

// VALIDATION TESTS
const auto neurites_attached_to_soma = [](const Neuron& n){
  auto test = neurostr::validator::neurites_attached_to_soma;
  test.validate(n);
};

const auto neuron_has_soma = [](const Neuron& n){
  auto test = neurostr::validator::neuron_has_soma;
  test.validate(n);
};

const auto planar_reconstruction_validator = [](const Neuron& n){
  auto test = neurostr::validator::planar_reconstruction_validator_factory(1.01);
  test.validate(n);
};

const auto dendrite_count_validator = [](const Neuron& n){
  auto test = neurostr::validator::dendrite_count_validator_factory(2,13);
  test.validate(n);
};

const auto apical_count_validator = [](const Neuron& n){
  auto test = neurostr::validator::apical_count_validator_factory(true);
  test.validate(n);
};

const auto axon_count_validator = [](const Neuron& n){
  auto test = neurostr::validator::axon_count_validator_factory(true);
  test.validate(n);
};

const auto no_trifurcations_validator = [](const Neuron& n){
  auto test = neurostr::validator::no_trifurcations_validator;
  test.validate(n);
};

const auto linear_branches_validator = [](const Neuron& n){
  auto test = neurostr::validator::linear_branches_validator_factory(1.01);
  test.validate(n);
};

const auto zero_length_segments_validator = [](const Neuron& n){
  auto test = neurostr::validator::zero_length_segments_validator;
  test.validate(n);
};

const auto increasing_radius_validator = [](const Neuron& n){
  auto test = neurostr::validator::increasing_radius_validator;
  test.validate(n);
};

const auto segment_collision_validator = [](const Neuron& n){
  auto test = neurostr::validator::segment_collision_validator;
  test.validate(n);
};

const auto extreme_angles_validator = [](const Neuron& n){
  auto test = neurostr::validator::extreme_angles_validator;
  test.validate(n);
};
// End validation fncs

void validation_benchmark(bmk::benchmark<std::chrono::microseconds>& bm, Neuron& m ){
  const int nrep = 5;
  bm.run("Attached to soma",nrep, [&](){neurites_attached_to_soma(m);});
  bm.run("Has soma",nrep, [&](){neuron_has_soma(m);});
  bm.run("Planar reconstruction",nrep, [&](){planar_reconstruction_validator(m);});
  bm.run("Dendrite count",nrep, [&](){dendrite_count_validator(m);});
  bm.run("Has apical",nrep, [&](){apical_count_validator(m);});
  bm.run("Has axon",nrep, [&](){axon_count_validator(m);});
  bm.run("Trifurcations check",nrep, [&](){no_trifurcations_validator(m);});
  bm.run("Linear branches",nrep, [&](){linear_branches_validator(m);});
  bm.run("Zero length segments",nrep, [&](){zero_length_segments_validator(m);});
  bm.run("Non-decreasing diameter",nrep, [&](){increasing_radius_validator(m);});
  bm.run("Segment collision",nrep, [&](){segment_collision_validator(m);});
  bm.run("Extreme angles",nrep, [&](){extreme_angles_validator(m);});
}

void lmeasures_benchmark(bmk::benchmark<std::chrono::microseconds>& bm, Neuron& n ){
  namespace nlm = neurostr::measure::lmeasure;
  const int nrep = 5;
  
  n.remove_null_segments();
  
  bm.run("soma_surface",nrep, [&](){nlm::soma_surface(n);});
  bm.run("n_stems",nrep, [&](){nlm::n_stems(n);});
  bm.run("n_bifs",nrep, [&](){nlm::n_bifs(n);});
  bm.run("n_branch",nrep, [&](){nlm::n_branch(n);});
  bm.run("n_tips",nrep, [&](){nlm::n_tips(n);});
  bm.run("width",nrep, [&](){nlm::width(n);});
  bm.run("height",nrep, [&](){nlm::height(n);});
  bm.run("depth",nrep, [&](){nlm::depth(n);});
  bm.run("diameter",nrep, [&](){nlm::diameter(n);});
  bm.run("diameter_pow",nrep, [&](){nlm::diameter_pow(n);});
  bm.run("length",nrep, [&](){nlm::length(n);});
  bm.run("surface",nrep, [&](){nlm::surface(n);});
  bm.run("section_area",nrep, [&](){nlm::section_area(n);});
  bm.run("volume",nrep, [&](){nlm::volume(n);});
  bm.run("euc_distance",nrep, [&](){nlm::euc_distance(n);});
  bm.run("path_distance",nrep, [&](){nlm::path_distance(n);});
  bm.run("branch_order",nrep, [&](){nlm::branch_order(n);});
  bm.run("terminal_degree",nrep, [&](){nlm::terminal_degree(n);});
  bm.run("taper_1",nrep, [&](){nlm::taper_1(n);});
  bm.run("taper_2",nrep, [&](){nlm::taper_2(n);});
  bm.run("branch_pathlength",nrep, [&](){nlm::branch_pathlength(n);});
  bm.run("contraction",nrep, [&](){nlm::contraction(n);});
  bm.run("fragmentation",nrep, [&](){nlm::fragmentation(n);});
  bm.run("daughter_ratio",nrep, [&](){nlm::daughter_ratio(n);});
  bm.run("partition_asymmetry",nrep, [&](){nlm::partition_asymmetry(n);});
  bm.run("rall_power",nrep, [&](){nlm::rall_power(n);});
  bm.run("pk",nrep, [&](){nlm::pk(n);});
  bm.run("pk_classic",nrep, [&](){nlm::pk_classic(n);});
  bm.run("pk_2",nrep, [&](){nlm::pk_2(n);});
  bm.run("bif_ampl_local",nrep, [&](){nlm::bif_ampl_local(n);});
  bm.run("bif_ampl_remote",nrep, [&](){nlm::bif_ampl_remote(n);});
  bm.run("bif_tilt_local",nrep, [&](){nlm::bif_tilt_local(n);});
  bm.run("bif_tilt_remote",nrep, [&](){nlm::bif_tilt_remote(n);});
  bm.run("bif_torque_local",nrep, [&](){nlm::bif_torque_local(n);});
  bm.run("bif_torque_remote",nrep, [&](){nlm::bif_torque_remote(n);});
  bm.run("last_parent_diam",nrep, [&](){nlm::last_parent_diam(n);});
  bm.run("hillman_threshold",nrep, [&](){nlm::hillman_threshold(n);});
  bm.run("fractal_dim",nrep, [&](){nlm::fractal_dim(n);});
}


int main()
{    
    const int nrep = 5;

    /** Read speed test **/
    // SWC READ SPEEd
    bmk::benchmark<std::chrono::microseconds> bm_swc;
    bm_swc.run("swc_read_small",nrep, load_file_test, "file", {swc_small});
    bm_swc.run("swc_read_medium",nrep, load_file_test, "file", {swc_med});
    bm_swc.run("swc_read_large",nrep, load_file_test, "file", {swc_large});
    bm_swc.print("swc_read", std::cout);
    
    
    // ASC READ SPEED
    bmk::benchmark<std::chrono::microseconds> bm_asc;
    //bm_asc.run("asc_read_small",10, load_file_test, "file", {asc_small}); // FIX FAIL #48
    bm_asc.run("asc_read_medium",nrep, load_file_test, "file", {asc_med});
    //bm_asc.run("asc_read_large",10, load_file_test, "file", {asc_large}); // FIX ISSUE #49
    bm_asc.print("asc_read", std::cout);
    
    // DAT READ SPEED
    bmk::benchmark<std::chrono::microseconds> bm_dat;
    bm_dat.run("dat_read_small",nrep, load_file_test, "file", {dat_small});
    bm_dat.run("dat_read_medium",nrep, load_file_test, "file", {dat_med});
    bm_dat.run("dat_read_large",nrep, load_file_test, "file", {dat_large});
    bm_dat.print("dat_read", std::cout);
    
    // JSON READ SPEEd
    //bmk::benchmark<std::chrono::microseconds> bm_json;
    //bm_json.run("json_read_small",10, load_file_test, "file", {json_small}); // FIX
    //bm_json.run("json_read_medium",10, load_file_test, "file", {json_med});
    //bm_json.run("json_read_large",10, load_file_test, "file", {json_large});
    //bm_json.print("json_read", std::cout);
    
    // Read small, medium and large
    auto r_small = neurostr::io::read_file_by_ext(swc_small);
    auto r_med = neurostr::io::read_file_by_ext(swc_med);
    auto r_large = neurostr::io::read_file_by_ext(swc_large);
    
    Neuron& n_small = *(r_small->begin());
    Neuron& n_med = *(r_med->begin());
    Neuron& n_large = *(r_large->begin());
    
    // Run Validation tests
    bmk::benchmark<std::chrono::microseconds> bm_validation_small;
    validation_benchmark(bm_validation_small,n_small);
    bm_validation_small.print("Validation - small size neuron", std::cout);
    
    
    bmk::benchmark<std::chrono::microseconds> bm_validation_med;
    validation_benchmark(bm_validation_med,n_med);
    bm_validation_med.print("Validation - med size neuron", std::cout);
    
    bmk::benchmark<std::chrono::microseconds> bm_validation_large;
    validation_benchmark(bm_validation_large,n_large);
    bm_validation_large.print("Validation - large size neuron", std::cout);
    
    bmk::benchmark<std::chrono::microseconds> bm_measures_small;
    lmeasures_benchmark(bm_measures_small, n_small);
    bm_measures_small.print("Measure - small size neuron", std::cout);
    
    bmk::benchmark<std::chrono::microseconds> bm_measures_med;
    lmeasures_benchmark(bm_measures_med, n_med);
    bm_measures_med.print("Measure - medium size neuron", std::cout);
    
    bmk::benchmark<std::chrono::microseconds> bm_measures_large;
    lmeasures_benchmark(bm_measures_large, n_med);
    bm_measures_large.print("Measure - large size neuron", std::cout);
}
