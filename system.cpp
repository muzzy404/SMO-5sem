#include "system.h"
#include "constants.h"

#include <stdexcept>
#include <iostream>  // for results printing
#include <algorithm> // for results, max_element
#include <cmath>     // for round
#include <cstdlib>   // srand
#include <ctime>     // time

System::System() :
  min_requests_(Constants::min_requests()),
  step_by_step_mode_(Constants::step_by_step_mode())
{
  const unsigned sources_num   = Constants::sources();
  const unsigned consumers_num = Constants::consumers();

  counter_ = std::make_shared<Counter>(sources_num);
  buffer_  = std::make_unique<Buffer>(Constants::buffer(), counter_);

  std::srand(std::time(0));

  for(unsigned i = 0; i < sources_num; ++i) {
    sources_.push_back(*(new Source(i, counter_)));
    sources_.at(i).next_time_point(); // generate time for first requests
  }

  for(unsigned i = 0; i <consumers_num; ++i) {
    consumers_.push_back(*(new Consumer(i, counter_)));
  }

  status_ = "system ready for simulation";
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
      unsigned min_consumer = find_min_consumer();
      consumers_.at(min_consumer).process_request(request);

      status_ = "rest processing: consumer " + std::to_string(min_consumer + 1);
    } catch (...) {
      // buffer is finally empty
      finished_     = true;
      process_rest_ = false;

      status_ = "simulation is over";
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
      std::string source_num_str = std::to_string(min_source + 1);
      try {
        buffer_->add(request);
        status_ = "source " + source_num_str + " sent request to buffer";
      } catch (...) {
        status_ = "rejection on source " + source_num_str;
      } // rejection

      // check for total generated requests during modeling
      if (counter_->total() == min_requests_) {
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

        status_ = "processing on consumer " + std::to_string(min_consumer + 1);
      } catch (...) { // buffer is empty
        // generate new request and put it into buffer for next iteration
        min_source = find_min_source();
        buffer_->add(sources_.at(min_source).get_request());

        status_ = "source " + std::to_string(min_source + 1) + " sent request to buffer";
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
  for(const Source & src : sources_) {
    std::cout << src.get_priority()     << " - time: "
              << src.get_current_time() << ", total: "
              << counter_->total(i)     << ", rejected: "
              << counter_->rejected(i)  << "\n";
    i++;
  }

  std::cout << "\n--- BUFFER ---\n";
  buffer_->print_reqs();

  std::cout << "\n--- CONSUMERS ---\n";
  for(const Consumer & cnm : consumers_) {
    std::cout << cnm.get_priority() << " - time: "
              << cnm.get_current_time() << "\n";
  }

  std::cout << "\nTOTAL: " << counter_->total()
            << "/"         << min_requests_ << "\n";
  std::cout << "================================================\n\n";
}

void System::print_result_table() const
{
  unsigned i = 0;
  for(const Source & src : sources_) {
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


  for(const Consumer & cnm : consumers_) {
    std::cout << "CONSUMER " << cnm.get_priority();
    std::cout << "\n  coefficient: "
              << counter_->count_device_coeff(total_time, cnm.get_current_time()) << "\n";

  }
  std::cout << "================================================\n\n";
}

System::buffer_state_t System::get_buffer_state() const
{
  return buffer_->get_state();
}

System::devices_state_t System::get_sources_state() const
{
  devices_state_t state;
  for(Source src : sources_) {
    state.push_back(src.get_state());
  }

  return state;
}

System::devices_state_t System::get_consumers_state() const
{
  devices_state_t state;
  for(Consumer cnmr : consumers_) {
    state.push_back(cnmr.get_state());
  }

  return state;
}

std::vector<double> System::get_devices_coeff() const
{
  double total_time = (*std::max_element(consumers_.begin(), consumers_.end(),
                          [](Consumer const & left, Consumer const & right)
                          {
                            return (left.get_current_time() < right.get_current_time());
                          })).get_current_time();

  std::vector<double> coefficients;

  for(const Consumer & cnmr : consumers_) {
    coefficients.push_back(counter_->count_device_coeff(total_time,
                                                        cnmr.get_current_time()));
  }

  return coefficients;
}

int System::get_progress() const
{
  double total = (double)(counter_->total());

  int progress = (int)(std::round(total / min_requests_ * 100));

  if ((progress == 100) && !finished_) {
    return (progress - 1);
  }

  return progress;
}
