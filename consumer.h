#ifndef CONSUMER_H
#define CONSUMER_H

#include "device.h"
#include "request.h"

#include <string>

class Consumer : public Device
{
public:
  Consumer(const unsigned, Counter_ptr);
  Consumer(const unsigned, const time_t, Counter_ptr);

  void process_request(Request::Request_ptr & request);

  void set_current_time(const double time) { current_time_ = time; }

  void next_time_point() override;

private:

};

#endif // CONSUMER_H
