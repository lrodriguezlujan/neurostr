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

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/format.hpp>

//#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>


#include <neurostr/core/log.h>
#include <neurostr/core/neuron.h>
#include <neurostr/io/parser_dispatcher.h>
#include <neurostr/validator/validator.h>
#include <neurostr/validator/predefined_validators.h>
#include <neurostr/measure/lmeasure_decl.h>

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

		os << ", \"factor_name\" : \"" << _fctName << "\""; 
		// print the factor list
		os << ", \"factors\" : [ "; 
		for (auto&& Pair : _timings) {
      os << token; 
			os << Pair.first; 
			token = ", "; 
    }
		os << " ]"; 
		// print the timings
		token.clear(); 
		os << ", \"timings\" : [ ";
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
		os << ", \"timings\" : [ ";
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
				os << "{ \"benchmark_name\" : \"" << benchmarkName << "\"";
				os << ", \"experiment_name\" : \"" << Pair.first << "\"";
				os << ", \"time_type\" : \"" << time_type<TimeT>() << "\"";
				Pair.second->print(os);
				os << " },\n";
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
				os << "{ \"benchmark_name\" : \"" << benchmarkName << "\"";
				os << ", \"experiment_name\" : \"" << Pair.first << "\"";
				os << ", \"time_type\" : \"" << time_type<TimeT>() << "\"";
				Pair.second->print(os);
				os << " } \n";
			}
			os.close(); 
		}
	};

} // ~ namespace bmk


/**** PROGRAM STARTS HERE! */

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

const auto radius_length_segments_validator = [](const Neuron& n){
  auto test = neurostr::validator::radius_length_segments_validator;
  test.validate(n);
};

const auto increasing_radius_validator = [](const Neuron& n){
  auto test = neurostr::validator::increasing_radius_validator;
  test.validate(n);
};

const auto segment_collision_validator = [](const Neuron& n){
  //auto test = neurostr::validator::segment_collision_validator;
  auto test = neurostr::validator::branch_collision_validator_factory(false);
  test.validate(n);
};

const auto extreme_angles_validator = [](const Neuron& n){
  auto test = neurostr::validator::extreme_angles_validator;
  test.validate(n);
};
// End validation fncs

void validation_benchmark(bmk::benchmark<std::chrono::microseconds>& bm, Neuron& m, int nrep){
  
  bm.run("Attached to soma",nrep, [&](){neurites_attached_to_soma(m);});
  bm.run("Has soma",nrep, [&](){neuron_has_soma(m);});
  bm.run("Planar reconstruction",nrep, [&](){planar_reconstruction_validator(m);});
  bm.run("Dendrite count",nrep, [&](){dendrite_count_validator(m);});
  bm.run("Has apical",nrep, [&](){apical_count_validator(m);});
  bm.run("Has axon",nrep, [&](){axon_count_validator(m);});
  bm.run("Trifurcations check",nrep, [&](){no_trifurcations_validator(m);});
  bm.run("Linear branches",nrep, [&](){linear_branches_validator(m);});
  bm.run("Zero length segments",nrep, [&](){zero_length_segments_validator(m);});
  bm.run("Radius length segments",nrep, [&](){radius_length_segments_validator(m);});
  bm.run("Non-decreasing diameter",nrep, [&](){increasing_radius_validator(m);});
  bm.run("Branch collision",nrep, [&](){segment_collision_validator(m);});
  bm.run("Extreme angles",nrep, [&](){extreme_angles_validator(m);});
}

void lmeasures_benchmark(bmk::benchmark<std::chrono::microseconds>& bm, Neuron& n, int nrep){
  namespace nlm = neurostr::measure::lmeasure;
  
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

namespace po = boost::program_options;

int main(int ac, char **av)
{    
    int nrep ;
    std::string ifile;
    
    
    // Program options declaration
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help,h", "Produce help message")
    ("input,i", po::value< std::string >(&ifile), "Neuron reconstruction file")
    ("nrep,n", po::value< int >(&nrep) -> default_value(100), "Number of repetitions per test");
    
      // Parse options into the variable map
    po::variables_map vm;
    try{
      po::store(po::command_line_parser(ac, av).options(desc).run(), vm);
      po::notify(vm);    
    } catch (std::exception e){
      // Something went wrong in the param. parsing
      NSTR_LOG_(error, "Unrecognized option");
      std::cout << desc << "\n";
      std::cout << "Example: neurostr_benchmark -i test.swc " << std::endl << std::endl ;
      return 1;
    }
    
    // Help option
    if (vm.count("help")){
      std::cout << desc << "\n";
      std::cout << "Example: neurostr_benchmark -i test.swc " << std::endl << std::endl ;
      return 2;
    }
  
    // Missing input/output
    if(!vm.count("input")){
      NSTR_LOG_(error, "Input/output file required");
      std::cout << desc << "\n";
      std::cout << "Example: neurostr_benchmark -i test.swc " << std::endl << std::endl ;
      return 3;
    }
    
    neurostr::log::init_log_cerr(); // Log to cerr
    
    // Validation speed
    auto r = neurostr::io::read_file_by_ext(ifile);
    Neuron& n = *(r->begin());
    
    auto nodecount = n.node_count();
    
    std::cout << "{ " << std::endl;
          
    std::cout << " \"file\": \" " << ifile << "\"," << std::endl;
    std::cout << " \"node_count\": " << std::to_string(nodecount) << "," << std::endl;
    
      
    std::cout << "\"benchmark\": [" << std::endl;
    
  
    /** Read speed test **/
    bmk::benchmark<std::chrono::microseconds> bm_read;
    bm_read.run("Read_speed",nrep, [_f = ifile](){auto  r = neurostr::io::read_file_by_ext(_f);});
    bm_read.print("Read", std::cout);
    
    // Run Validation tests
    bmk::benchmark<std::chrono::microseconds> bm_validation;
    validation_benchmark(bm_validation,n, nrep);
    bm_validation.print("Validation", std::cout);
    
    // Run Measure test
    bmk::benchmark<std::chrono::microseconds> bm_measures;
    lmeasures_benchmark(bm_measures, n, nrep);
    bm_measures.print("Measures", std::cout);
    
    // Mock object and close
    std::cout << " {}]} "<< std::endl;
}
