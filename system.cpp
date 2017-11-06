#include "system.h"
#include "constants.h"

#include <stdexcept>
#include <iostream>  // for results printing
#include <algorithm> // for results, max_element

System::System()
{
  const unsigned sources_num   = Constants::sources();
  const unsigned consumers_num = Constants::consumers();

  counter_ = std::make_shared<Counter>(sources_num);
  buffer_  = std::make_unique<Buffer>(Constants::buffer(), counter_);

  for(unsigned i = 0; i < sources_num; ++i) {
    sources_.push_back(*(new Source(i, counter_)));
    sources_.at(i).next_time_point(); // generate time for first requests
  }

  for(unsigned i = 0; i <consumers_num; ++i) {
    consumers_.push_back(*(new Consumer(i, counter_)));
  }
}

void System::next_iteration()
{
  if (finished_) {
    throw std::runtime_error("modeling finished");
  }

  typedef Request::Request_ptr Req_ptr;

  // process rest in buffer after stop condition reached
  if (process_rest_)
  {
    try {
      Req_ptr request = buffer_->get();
      consumers_.at(find_min_consumer()).process_request(request);

    } catch (...) {
      // buffer is finally empty
      finished_     = true;
      process_rest_ = false;
    }
    return; // only rest requests processing
  }

  // normal modeling iteration
  unsigned min_source   = find_min_source();
  unsigned min_consumer = find_min_consumer();

  // find min device with min time
  devices_group device = SOURCE;
  if (consumers_.at(min_consumer).get_current_time() <
          sources_.at(min_source).get_current_time()) {
    device = CONSUMER;
  }

  switch (device) {
    case SOURCE:
    {
      Req_ptr request = sources_.at(min_source).get_request();
      try {
        buffer_->add(request);
      } catch (...) {} // rejection

      // check for total generated requests during modeling
      if (counter_->total() == Constants::min_requests()) {
        process_rest_ = true;
        // now it's time to stop generation and process rest in buffer
      }

      break;
    }
    case CONSUMER:
    {
      try {
        Req_ptr request = buffer_->get();
        consumers_.at(min_consumer).process_request(request);
      } catch (...) { // buffer is empty
        // generate new request and put it into buffer for next iteration
        min_source = find_min_source();
        buffer_->add(sources_.at(min_source).get_request());
      }

      break;
    }
    } // switch end
}

template < typename T >
unsigned System::find_min_time(const std::vector<T> & devices) const
{
  unsigned min_time_index = 0;
  double   min_time = devices.at(min_time_index).get_current_time();

  for(unsigned i = min_time_index + 1; i < devices.size(); ++i) {

    double time = devices.at(i).get_current_time();

    if (time < min_time) {
      min_time_index = i;
      min_time = time;
    }
  }
  return min_time_index;
}

unsigned System::find_min_source() const
{
  return find_min_time(sources_);
}

unsigned System::find_min_consumer() const
{
  return find_min_time(consumers_);
}


void System::print_calendar() const
{
  std::cout << "--- SOURCES ---\n";
  unsigned i = 0;
  for(Source src : sources_) {
    std::cout << src.get_priority()     << " - time: "
              << src.get_current_time() << ", total: "
              << counter_->total(i)      << ", rejected: "
              << counter_->rejected(i)   << "\n";
    i++;
  }

  std::cout << "\n--- BUFFER ---\n";
  buffer_->print_reqs();

  std::cout << "\n--- CONSUMERS ---\n";
  for(Consumer cnm : consumers_) {
    std::cout << cnm.get_priority() << " - time: "
              << cnm.get_current_time() << "\n";
  }

  std::cout << "\nTOTAL: " << counter_->total()
            << "/"         << Constants::min_requests() << "\n";
  std::cout << "================================================\n\n";
}

void System::print_result_table() const
{
  unsigned i = 0;
  for(Source src : sources_) {
    std::cout << "SOURCE "    << src.get_priority();
    std::cout << "\n  total       : " << counter_->total(i);
    std::cout << "\n  rejected    : " << counter_->rejected(i);
    std::cout << "\n  P[rejection]: " << counter_->get_rejection_probability(i) << "%";
    std::cout << "\n  T[in system]: " << counter_->get_in_system_time(i);
    std::cout << "\n  T[waiting]  : " << counter_->get_waiting_time(i);
    std::cout << "\n  T[service]  : " << counter_->get_service_time(i);
    std::cout << "\n  D[waiting]  : " << counter_->get_waiting_dispersion(i);
    std::cout << "\n  D[service]  : " << counter_->get_service_dispersion(i) << "\n\n";
    ++i;
  }
  std::cout << "================================================\n\n";


  // MAX or MIN?
  double total_time = (*std::max_element(consumers_.begin(), consumers_.end(),
                          [](Consumer const & left, Consumer const & right)
                          {
                            return (left.get_current_time() < right.get_current_time());
                          })).get_current_time();
  std::cout << "REALISATION TIME = " << total_time << "\n\n";


  for(Consumer cnm : consumers_) {
    std::cout << "CONSUMER " << cnm.get_priority();
    std::cout << "\n  coefficient: "
              << counter_->count_device_coeff(total_time, cnm.get_current_time()) << "\n";

  }
  std::cout << "================================================\n\n";
}
