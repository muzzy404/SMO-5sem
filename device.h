#ifndef DEVICE_H
#define DEVICE_H

#include "counter.h"

#include <stdexcept>
#include <utility>
#include <string>
#include <sstream>
#include <iomanip>

class Device
{
public:
  typedef Counter::Counter_ptr Counter_ptr;
  typedef std::pair<std::string, std::string> state_t;
  typedef Counter::time_t time_t;

  Device(const unsigned priority, const time_t time, Counter_ptr counter) :
      priority_(priority),
      current_time_(time),
      last_request_("none")
  {
    if (counter == nullptr) {
      throw std::invalid_argument("counter must be not null");
    }
    counter_ = counter;
  }

  Device(const unsigned priority, Counter_ptr counter) :
    Device(priority, 0.0, counter)
  {}

  unsigned get_priority()     const { return priority_;     }
  time_t   get_current_time() const { return current_time_; }

  virtual void next_time_point() = 0;

  state_t get_state() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(5) << this->current_time_;

    return std::make_pair(ss.str(), last_request_);
  }

protected:
  const unsigned priority_;
  time_t         current_time_;
  std::string    last_request_;

  Counter_ptr counter_;
};

#endif // DEVICE_H
