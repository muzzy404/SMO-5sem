#ifndef BUFFER_H
#define BUFFER_H

#include "request.h"
#include "counter.h"

#include <vector>
#include <string>

class Buffer
{
public:
  typedef Request::Request_ptr Request_ptr;
  typedef Counter::Counter_ptr Counter_ptr;

  Buffer(const unsigned size, Counter_ptr counter);

  void add(const Request_ptr request);
  Request_ptr get();

  void print_reqs() const;

  std::vector<std::string> get_state() const;

private:
  std::vector<Request_ptr> buffer_;

  Counter_ptr counter_;

  int occupied_;
};

#endif // BUFFER_H
