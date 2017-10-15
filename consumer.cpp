#include "consumer.h"
#include "counter.h"

Consumer::Consumer(const long priority) :
  Device(priority)
{}

Consumer::Consumer(const long priority, const double time) :
  Device(priority, time)
{}

void Consumer::process_request(Request::Request_ptr request)
{
  //count time in buffer
  Counter::add_to_buffer_time(current_time_ - request->get_creation_time());

  next_time_point();
}

void Consumer::next_time_point()
{
  //TODO: gen function
  current_time_ += 10;
}
