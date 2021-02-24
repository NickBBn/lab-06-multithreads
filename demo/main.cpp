#include <hash_calculator.hpp>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>
#include <csignal>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;

BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", boost::log::trivial::severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(thread_id, "ThreadID", boost::log::attributes::current_thread_id::value_type)

void logging_init(){
  typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
  boost::shared_ptr< text_sink > sink = boost::make_shared< text_sink >();
  sink->locked_backend()->add_stream(
      boost::make_shared< std::ofstream >("sample.log"));
  boost::shared_ptr< std::ostream > stream(&std::clog, logging::empty_deleter());
  sink->locked_backend()->add_stream(stream);
  boost::log::formatter formatter = expr::stream
      << std::setw(7) << std::setfill('0') << line_id << std::setfill(' ') << " | "
      << "T." << thread_id << " | "
      << expr::format_date_time(timestamp, "%Y-%m-%d, %H:%M:%S.%f") << " "
      << "[" << severity << "]"
      << " - " << expr::smessage;
  sink->set_formatter(formatter);
  logging::core::get()->add_sink(sink);
  logging::add_common_attributes();
}

void stop_calculation([[maybe_unused]] int exit_param) {
  hash_calculator::close_threads = true;
}

void safe_exit() {
  boost::shared_ptr< logging::core > core = logging::core::get();
  core->flush();
  core->remove_all_sinks();
  delete hash_calculator::json_struct;
}

hash_calculator::json_structure* hash_calculator::json_struct = nullptr;
std::atomic<bool> hash_calculator::close_threads = false;
std::mutex hash_calculator::json_mutex;

void calculation(){
  BOOST_LOG_TRIVIAL(trace) << "Opened new Thread";
  hash_calculator calc;
  calc.calculate_hash();
}

void manage_params(const int& argc, char* argv[], unsigned &number_of_threads){
  const std::string json_extension = ".json";
  switch (argc){
    case 1 :
      number_of_threads = std::thread::hardware_concurrency();
      break;
    case 2 :
      try {
        number_of_threads = std::stoi(argv[1]);
      } catch (const std::invalid_argument& e) {
        hash_calculator::json_struct = new hash_calculator::json_structure(argv[1] + json_extension);
        number_of_threads = std::thread::hardware_concurrency();
      }
      break;
    case 3:
      try {
        number_of_threads = std::stoi(argv[1]);
      } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Invalid arguments: number of threads must be integer ");
      }
      hash_calculator::json_struct = new hash_calculator::json_structure(argv[2] + json_extension);
      break;
    default:
      throw std::invalid_argument("Invalid arguments: Program needs two or less parameters ");
  }
  std::cout << "Recommended number of threads: "
            << std::thread::hardware_concurrency() << std::endl
            << "number of threads: " << number_of_threads << std::endl;
}

int main(int argc, char* argv[]) {
  std::signal(SIGINT, stop_calculation);
  std::srand(std::time(nullptr));
  logging_init();
  unsigned number_of_threads = 0;
  try {
    manage_params(argc, argv, number_of_threads);
  } catch (const std::invalid_argument &error) {
    std::cout << error.what();
    return -1;
  }
  std::vector<std::thread> threads;
  for (unsigned i = 0; i < number_of_threads; ++i)
    threads.emplace_back(std::thread(calculation));
  for (auto& thread : threads) thread.join();
  safe_exit();
  return 0;
}
