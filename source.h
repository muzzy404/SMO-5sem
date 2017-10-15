#ifndef SOURCE_H
#define SOURCE_H

#include "device.h"
#include "request.h"

class Source : public Device
{
public:
  Source(const unsigned,Counter_ptr);
  Source(const unsigned, const double, Counter_ptr counter);

  Request::Request_ptr get_request();

  void next_time_point();

private:
  unsigned requests_num_;
};

#endif // SOURCE_H
