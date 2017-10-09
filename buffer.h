#ifndef BUFFER_H
#define BUFFER_H

#include<request.h>

#include <vector>
#include <memory> // shared_ptr

class Buffer
{
public:
  typedef std::shared_ptr<Request>       Request_ptr;
  typedef std::shared_ptr<const Request> Request_ptr_const;

  Buffer(const int size);

  void add(const Request_ptr request);
  Request_ptr get();

  void print_reqs() const;

private:
  std::vector<Request_ptr> buffer_;

  int occupied_;
};

#endif // BUFFER_H
