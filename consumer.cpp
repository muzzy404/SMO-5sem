#include "consumer.h"
#include "constants.h"

#include <cmath>    // std::log()

Consumer::Consumer(const unsigned priority, Counter_ptr counter) :
  Device(priority, counter)
{}

Consumer::Consumer(const unsigned priority, const time_t time, Counter_ptr counter) :
  Device(priority, time, counter)
{}

void Consumer::process_request(Request::Request_ptr & request)
{
  if (request->get_creation_time() > current_time_)
  {
    // if consumer was waiting for request
    current_time_ = request->get_creation_time();
  }

  unsigned i = request->get_priority();

  time_t entrance_time = current_time_;
  time_t creation_time = request->get_creation_time();

  counter_->add_in_buffer_time(i, current_time_ - creation_time);

  next_time_point();

  counter_->add_service_time(i,   current_time_ - entrance_time);
  counter_->add_in_system_time(i, current_time_ - creation_time);

  last_request_ = (std::to_string(request->get_priority()) +
                   "." +
                   std::to_string(request->get_number()));
}

void Consumer::next_time_point()
{
  // exponential
  current_time_ += -(1.0 / Constants::lambda()) *
                   std::log(1.0 - Constants::distribution());
}


