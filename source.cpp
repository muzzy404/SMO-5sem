#include "source.h"
#include "constants.h"

#include <iostream> // TODO: remove

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
  last_generated_ = (std::to_string(priority_) +
                     "." +
                     std::to_string(requests_num_));
}

void Source::next_time_point()
{
  // equable
  current_time_ += Constants::distribution() *
                  (Constants::beta() - Constants::alpha())
                                     + Constants::alpha();
}

Device::state_t Source::get_state() const
{
  return std::make_pair(std::to_string(this->current_time_),
                        last_generated_);
}
