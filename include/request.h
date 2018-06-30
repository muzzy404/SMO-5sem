#ifndef REQUEST_H
#define REQUEST_H

#include <memory> // shared_ptr

class Request
{
public:
  typedef std::shared_ptr<Request> Request_ptr;

  Request(unsigned priority, unsigned number, double time);
  ~Request();

  unsigned get_priority() const { return priority_; }
  unsigned get_number()   const { return number_;   }

  double get_creation_time() const { return creation_time_; }

private:
  const unsigned priority_;
  const unsigned number_;

  const double creation_time_;

};

#endif // REQUEST_H
