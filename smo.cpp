#include "smo.h"
#include "buffer.h"
#include "constants.h"

#include <memory>     // std::shared_ptr
#include <stdexcept>
#include <iostream>

SMO::Time_group min_time_group_ = SMO::UNDEFINED;
unsigned        min_time_index_ = 0;

void SMO::main_loop()
{
  std::shared_ptr<Counter> counter = std::make_shared<Counter>(Constants::buffer());
  Buffer buffer(counter->size(), counter);

  Sources   sources;
  Consumers consumers;

  // create and generate first time point
  for(unsigned i = 0; i < Constants::sources(); ++i) {
    sources.push_back(* (new Source(i, counter)));
    sources.at(i).next_time_point();
  }
  for(unsigned i = 0; i < Constants::consumers(); ++i) {
    consumers.push_back(* (new Consumer(i, counter)));
    consumers.at(i).next_time_point();
  }

  bool stop = false;

  while(!stop) {
    Min_time_t min_time = find_min_time(sources, consumers);

    switch (min_time.first) {
    case SOURCE: {
      unsigned min = min_time.second;

      Request_ptr request = sources.at(min).get_request();
      buffer.add(request);

      // TODO: check this statment in manual
      // max number of requests on some source
      if (counter->total(min) == Constants::min_requests()) {
        stop = true;
      }
      break;
    }

    case CONSUMER: {
      unsigned min = min_time.second;

      try{
        std::cout << "GET\n";
        Request_ptr request = buffer.get();
        consumers.at(min).process_request(request);
      } catch (std::exception & e) {
        std::cout << e. what() << "\n";
      }
      break;
    }

    default:
      std::cout << "definition error\n";
      break;
    }

    std::cout << "\nBUFFER\n";
    buffer.print_reqs();
    std::cout << "\n\n";
  } // while end

  std::cout << "REST IN BUFFER\n";
  buffer.print_reqs();

}

SMO::Min_time_t SMO::find_min_time(const Sources   & sources,
                                   const Consumers & consumers)
{
  Time_group min_time_group = SOURCE;
  unsigned   min_time_index = 0;
  double min_time = sources.at(min_time_index).get_current_time();

  for(unsigned i = min_time_index + 1; i < sources.size(); ++i) {
    if (sources.at(i).get_current_time() < min_time) {
      min_time_index = i;
      min_time = sources.at(i).get_current_time();
    }
  }

  for(unsigned i = 0; i < consumers.size(); ++i) {
    if (consumers.at(i).get_current_time() < min_time) {
      min_time_group = CONSUMER;
      min_time_index = i;
      min_time = consumers.at(i).get_current_time();
    }
  }

  return std::make_pair(min_time_group, min_time_index);
}
