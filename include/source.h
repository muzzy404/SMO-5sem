#ifndef SOURCE_H
#define SOURCE_H

#include "device.h"
#include "request.h"

#include <string>

class Source : public Device
{
public:
  Source(const unsigned, Counter_ptr);
  Source(const unsigned, const time_t, Counter_ptr);

  Request::Request_ptr get_request();

  void next_time_point() override;

private:
  unsigned requests_num_;
};

#endif // SOURCE_H
