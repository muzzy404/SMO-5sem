#ifndef CONSUMER_H
#define CONSUMER_H

#include "device.h"
#include "request.h"

class Consumer : public Device
{
public:
  Consumer(const unsigned, Counter_ptr);
  Consumer(const unsigned, const double, Counter_ptr);

  void process_request(Request::Request_ptr & request);

  void next_time_point() override;

  void set_current_time(const double time);

private:
  bool worked_;
};

#endif // CONSUMER_H
