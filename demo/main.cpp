#include <fstream>
#include <hash_calculator.hpp>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace expr = boost::log::expressions;

void calculation() {
  hash_calculator calc;
  calc.calculate_hash();
}

int* hash_calculator::a = nullptr;
void logging_init(){
/*
  boost::shared_ptr< logging::core > core = logging::core::get();
  boost::shared_ptr< sinks::text_file_backend > backend =
      boost::make_shared< sinks::text_file_backend >(
          keywords::file_name = "file_%5N.log",
          keywords::rotation_size = 5 * 1024 * 1024,
          keywords::format = "[%TimeStamp%]: %Message%",
          keywords::time_based_rotation =
              sinks::file::rotation_at_time_point(12, 0, 0));
  typedef sinks::synchronous_sink<sinks::text_file_backend> text_sink;
  boost::shared_ptr<text_sink> sink(new text_sink(backend));
  //sink->locked_backend()->add_stream(backend);
  core->add_sink(sink);
  logging::add_console_log();
  core->add_global_attribute("TimeStamp", logging::attributes::local_clock());
 // logging::add_file_log("file");
  //logging::add_common_attributes();
  */
  typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
  boost::shared_ptr< text_sink > sink = boost::make_shared< text_sink >();

  sink->locked_backend()->add_stream(
      boost::make_shared< std::ofstream >("sample.log"));

  sink->set_formatter
      (
          expr::format("%1%: <%2%> %3%")
          % expr::attr< unsigned int >("ThreadID")
          % logging::trivial::severity
          % expr::smessage
      );

  logging::core::get()->add_sink(sink);
}

int main(int argc, char* argv[]) {
  logging_init();
  logging::sources::logger lg;
  BOOST_LOG(lg) << "A trace severity message";
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
  return 0;
}
