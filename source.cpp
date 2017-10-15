#include "source.h"
#include "constants.h"
#include "counter.h"

Source::Source(const unsigned priority, Counter_ptr counter) :
  Device(priority, counter),
  requests_num_(0)
{}

Source::Source(const unsigned priority, const double time, Counter_ptr counter) :
  Device(priority, time, counter),
  requests_num_(0)
{}

Request::Request_ptr Source::get_request()
{
  double creation_time = current_time_;
  next_time_point();

  counter_->add_request(priority_);
  return std::make_shared<Request>(priority_,
                                   ++requests_num_,
                                   creation_time);
}

void Source::next_time_point()
{
  // equable
  current_time_ += Constants::distribution() *
                  (Constants::get_beta() - Constants::get_alpha())
                                         + Constants::get_alpha();
}
