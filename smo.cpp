#include "smo.h"
#include "constants.h"

#include <memory>     // std::shared_ptr
#include <stdexcept>
#include <algorithm>
#include <iostream>

void SMO::main_loop()
{
  Counter_ptr counter = std::make_shared<Counter>(Constants::sources());
  Buffer buffer(Constants::buffer(), counter);

  Sources   sources;
  Consumers consumers;

  // create
  for(unsigned i = 0; i < counter->size(); ++i) {
    sources.push_back(* (new Source(i, counter)));
    sources.at(i).next_time_point(); // generate time for first requests
  }
  for(unsigned i = 0; i < Constants::consumers(); ++i) {
    consumers.push_back(* (new Consumer(i, counter)));
  }

  bool stop = false;

  // MAIN LOOP
  while(!stop) {
    std::getchar();
    print_calendar(sources, consumers, buffer, counter);

    Min_time_t min_time = find_min_time(sources, consumers);
    unsigned min = min_time.second;

    switch (min_time.first) {

    case SOURCE: { // min time on source
      Request_ptr request = sources.at(min).get_request();
      try{
        buffer.add(request);
      } catch (std::exception & e) { // rejection
        std::cout << e.what() << "\n";
      }

      // max number of requests in system -> stop generate new
      if (counter->total() == Constants::min_requests()) {
        stop = true;
        std::cout << "~~~ LAST REQUEST ADDED TO BUFFER~~~\n\n";
      }
      break;
    }

    case CONSUMER: { // min time on consumer
      try{
        Request_ptr request = buffer.get();
        consumers.at(min).process_request(request);
      } catch (std::exception & e) { // empty buffer
        // put request into buffer and go to next iteration
        min = find_min_time(sources);
        buffer.add(sources.at(min).get_request());
      }
      break;
    }
    } // swithch end
  }   // while end

  // PROCESSING OF REST REQUESTS IN BUFFER
  while (true) {
    std::getchar();
    print_calendar(sources, consumers, buffer, counter);

    Request_ptr request;
    try{
      request = buffer.get();
    } catch (std::exception & e) { // buffer is empty
      std::cout << "\n~~~ BUFFER IS EMPTY ~~~\n";
      break;
    }
    // buffer is NOT empty -> processing of next request
    consumers.at(find_min_time(consumers)).process_request(request);
  }

  std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
  print_result_table(sources, consumers, counter);
}

SMO::Min_time_t SMO::find_min_time(const Sources   & sources,
                                   const Consumers & consumers)
{
  Time_group min_time_group = SOURCE;
  unsigned   min_time_index = 0;
  double     min_time       = sources.at(min_time_index).get_current_time();

  // search min time index in sources
  for(unsigned i = min_time_index + 1; i < sources.size(); ++i) {
    double time = sources.at(i).get_current_time();

    if (time < min_time) {
      min_time_index = i;
      min_time = sources.at(i).get_current_time();
    }

  }

  // search min time index in consumers
  for(unsigned i = 0; i < consumers.size(); ++i) {
    double time = consumers.at(i).get_current_time();

    if (time < min_time) {
      min_time_group = CONSUMER;
      min_time_index = i;
      min_time = time;
    }

  }

  return std::make_pair(min_time_group, min_time_index);
}

template < typename T >
unsigned SMO::find_min_time(const std::vector<T> & devices)
{
  unsigned min_time_index = 0;
  double   min_time       = devices.at(min_time_index).get_current_time();

  for(unsigned i = min_time_index + 1; i < devices.size(); ++i) {
    double time = devices.at(i).get_current_time();

    if (time < min_time) {
      min_time_index = i;
      min_time = time;
    }

  }

  return min_time_index;
}

void SMO::print_calendar(const Sources     & sources,
                         const Consumers   & consumers,
                         const Buffer      & buffer,
                         const Counter_ptr & counter)
{
  std::cout << "--- SOURCES ---\n";
  unsigned i = 0;
  for(Source src : sources) {
    std::cout << src.get_priority()     << " - time: "
              << src.get_current_time() << ", total: "
              << counter->total(i)      << ", rejected: "
              << counter->rejected(i)   << "\n";
    i++;
  }

  std::cout << "\n--- BUFFER ---\n";
  buffer.print_reqs();

  std::cout << "\n--- CONSUMERS ---\n";
  for(Consumer cnm : consumers) {
    std::cout << cnm.get_priority() << " - time: "
              << cnm.get_current_time() << "\n";
  }

  std::cout << "\nTOTAL: " << counter->total()
            << "/"         << Constants::min_requests() << "\n";
  std::cout << "================================================\n\n";
}

void SMO::print_result_table(const Sources     & sources,
                             const Consumers   & consumers,
                             const Counter_ptr & counter)
{
  unsigned i = 0;
  for(Source src : sources) {
    std::cout << "SOURCE "    << src.get_priority();
    std::cout << "\n  total       : " << counter->total(i);
    std::cout << "\n  rejected    : " << counter->rejected(i);
    std::cout << "\n  P[rejection]: " << counter->get_rejection_probability(i) << "%";
    std::cout << "\n  T[in system]: " << counter->get_in_system_time(i);
    std::cout << "\n  T[waiting]  : " << counter->get_waiting_time(i);
    std::cout << "\n  T[service]  : " << counter->get_service_time(i);
    std::cout << "\n  D[waiting]  : " << counter->get_waiting_dispersion(i);
    std::cout << "\n  D[service]  : " << counter->get_service_dispersion(i) << "\n\n";
    ++i;
  }
  std::cout << "================================================\n\n";


  double total_time = (*std::min_element(consumers.begin(), consumers.end(),
                        [](Consumer const & left, Consumer const & right)
                        {
                          return (left.get_current_time() < right.get_current_time());
                        })).get_current_time();
  std::cout << "REALISATION TIME = " << total_time << "\n\n";

  for(Consumer cnm : consumers) {
    std::cout << "CONSUMER " << cnm.get_priority();
    std::cout << "\n  coefficient: "
              << counter->count_device_coeff(total_time, cnm.get_current_time()) << "\n";

  }
  std::cout << "================================================\n\n";
}