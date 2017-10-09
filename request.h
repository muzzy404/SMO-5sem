#ifndef REQUEST_H
#define REQUEST_H


class Request
{
public:
  Request(long priority, long number, double time);
  ~Request();

  long get_priority() const { return priority_; }
  long get_number()   const { return number_;   }

  double get_creation_time() const { return creation_time_; }


private:
  const long priority_;
  const long number_;

  const double creation_time_;

};

#endif // REQUEST_H
