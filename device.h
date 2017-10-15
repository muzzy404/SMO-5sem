#ifndef DEVICE_H
#define DEVICE_H

class Device
{
public:
  Device(const long priority) :
      priority_(priority),
      current_time_(0.0)
  {}

  Device(const long priority, const double time) :
      priority_(priority),
      current_time_(time)
  {}

  long   get_priority()     const { return priority_; }
  double get_current_time() const { return current_time_; }

protected:
  virtual void next_time_point() = 0;

  const long priority_;
  double     current_time_;
};

#endif // DEVICE_H
