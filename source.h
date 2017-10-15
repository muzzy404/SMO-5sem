#ifndef SOURCE_H
#define SOURCE_H

#include "device.h"
#include "request.h"

class Source : public Device
{
public:
  Source(const long);
  Source(const long, const double);

  Request::Request_ptr get_request();

private:
  void next_time_point();

  long requests_num_;
};

#endif // SOURCE_H
