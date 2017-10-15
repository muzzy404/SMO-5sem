#include "consumer.h"
#include "counter.h"

Consumer::Consumer(const unsigned priority, Counter_ptr counter) :
  Device(priority, counter)
{}

Consumer::Consumer(const unsigned priority, const double time, Counter_ptr counter) :
  Device(priority, time, counter)
{}

void Consumer::process_request(Request::Request_ptr request)
{
  auto i = request->get_priority();
  auto entrance_time = current_time_;
  auto creation_time = request->get_creation_time();

  counter_->add_in_buffer_time(i, current_time_ - creation_time);

  next_time_point();

  counter_->add_service_time(i,   current_time_ - entrance_time);
  counter_->add_in_system_time(i, current_time_ - creation_time);
}

void Consumer::next_time_point()
{
  //TODO: gen function
  current_time_ += 10.0;
}
