#ifndef BUFFER_H
#define BUFFER_H

#include <request.h>

#include <vector>

class Buffer
{
public:
  typedef Request::Request_ptr Request_ptr;

  Buffer(const int size);

  void add(const Request_ptr request);
  Request_ptr get();

  void print_reqs() const;

private:
  std::vector<Request_ptr> buffer_;

  int occupied_;
};

#endif // BUFFER_H
