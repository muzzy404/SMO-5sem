#ifndef SOURCE_H
#define SOURCE_H

#include "device.h"
#include "request.h"

#include <string>

class Source : public Device
{
public:
  Source(const unsigned, Counter_ptr);
  Source(const unsigned, const double, Counter_ptr counter);

  Request::Request_ptr get_request();

  void next_time_point() override;

  Device::state_t get_state() const override;

private:
  unsigned    requests_num_;
  std::string last_generated_;
};

#endif // SOURCE_H
