#include "consumer.h"
#include "constants.h"

#include <cmath>    // std::log()
#include <iostream> // TODO: remove

Consumer::Consumer(const unsigned priority, Counter_ptr counter) :
  Device(priority, counter)
{}

Consumer::Consumer(const unsigned priority, const double time, Counter_ptr counter) :
  Device(priority, time, counter)
{}

void Consumer::process_request(Request::Request_ptr & request)
{
  // TODO: remove ?
  std::cout << "CONSUMER: processing on " << priority_;
  std::cout << " - request " << request->get_priority() <<
                         "." << request->get_number()   << "\n\n";

  if (request->get_creation_time() > current_time_)
  {
    // if consumer was waiting for request
    current_time_ = request->get_creation_time();
  }

  unsigned i = request->get_priority();

  double entrance_time = current_time_;
  double creation_time = request->get_creation_time();

  std::cout << "WAITING = " << (current_time_ - creation_time) << "\n";

  counter_->add_in_buffer_time(i, current_time_ - creation_time);

  next_time_point();

  counter_->add_service_time(i,   current_time_ - entrance_time);
  counter_->add_in_system_time(i, current_time_ - creation_time);
}

void Consumer::next_time_point()
{
  // exponential
  current_time_ += -(1.0 / Constants::lambda()) *
                   std::log(1.0 - Constants::distribution());
}

