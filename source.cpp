#include "source.h"
#include "constants.h"
#include "counter.h"

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
  // TODO: remove
  std::cout << "SOURCE: new request on " << priority_;
  std::cout << " - request " << priority_ <<
                         "." << (requests_num_ + 1) << "\n\n";

  counter_->set_realisation_time(current_time_);

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
                  (Constants::beta() - Constants::alpha())
                                     + Constants::alpha();
  /*std::cout << "current time on " << priority_
            << " source: "        << current_time_ << "\n";*/
}
