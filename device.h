#ifndef DEVICE_H
#define DEVICE_H

#include "counter.h"

#include <stdexcept>
#include <utility>

class Device
{
public:
  typedef Counter::Counter_ptr Counter_ptr;
  typedef std::pair<std::string, std::string> state_t;

  Device(const unsigned priority, const double time, Counter_ptr counter) :
      priority_(priority),
      current_time_(time)
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
  double   get_current_time() const { return current_time_; }

  virtual void    next_time_point() = 0;
  virtual state_t get_state() const = 0;

protected:
  const unsigned priority_;
  double         current_time_;

  Counter_ptr counter_;
};

#endif // DEVICE_H
