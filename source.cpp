#include "source.h"
#include "constants.h"
#include "counter.h"

//#include <cstdlib> for std::rand()

Source::Source(const long priority) :
  Device(priority),
  requests_num_(0)
{}

Source::Source(const long priority, const double time) :
  Device(priority, time),
  requests_num_(0)
{}

Request::Request_ptr Source::get_request()
{
  double creation_time = current_time_;
  next_time_point();

  Counter::add_to_total();
  return std::make_shared<Request>(priority_,
                                   requests_num_++,
                                   creation_time);
}

void Source::next_time_point()
{
  // TODO: gen time function
  current_time_ += 5;
}
