#include <fstream>
#include <hash_calculator.hpp>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;

BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", boost::log::trivial::severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(thread_id, "ThreadID", boost::log::attributes::current_thread_id::value_type)


int* hash_calculator::a = nullptr;
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
      << "[" << boost::log::trivial::severity << "]"
      << " - " << expr::smessage;
  sink->set_formatter(formatter);
  logging::core::get()->add_sink(sink);
  logging::add_common_attributes();
}

void stop_logging(){
  boost::shared_ptr< logging::core > core = logging::core::get();
  core->flush();
  core->remove_all_sinks();
}

void calculation() {
  hash_calculator calc;
  calc.calculate_hash();
}

int main(int argc, char* argv[]) {
  logging_init();
  BOOST_LOG_TRIVIAL(info) << "A trace severity message";
  hash_calculator::a = new int(25);
  unsigned number_of_threads = 0;
  switch (argc){
    case 1 :
      number_of_threads = std::thread::hardware_concurrency();
      break;
    case 2 :
      try {
        number_of_threads = std::stoi(argv[1]);
      } catch (const std::invalid_argument& e) {
        std::cout << "Invalid arguments: argument is not integer " << std::endl;
        return -1;
      }
      break;
    default:
      std::cout << "invalid arguments: program needs one argument" << std::endl;
      return -1;
  }
  std::cout << "Recommended number of threads: "
            << std::thread::hardware_concurrency() << std::endl
            << "number of threads: " << number_of_threads << std::endl;

  std::vector<std::thread> threads;
  for (unsigned i = 0; i < number_of_threads; ++i){
    threads.emplace_back(std::thread(calculation));
  }
  for (auto& thread : threads)
  {
    thread.join();
  }
  stop_logging();
  return 0;
}
