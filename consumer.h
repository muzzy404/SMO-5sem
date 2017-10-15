#ifndef CONSUMER_H
#define CONSUMER_H

#include "device.h"
#include "request.h"

class Consumer : public Device
{
public:
  Consumer(const long);
  Consumer(const long, const double);

  void process_request(Request::Request_ptr request);

private:
  void next_time_point();

};

#endif // CONSUMER_H
