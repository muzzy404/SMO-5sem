#ifndef SMO_H
#define SMO_H

#include "source.h"
#include "consumer.h"
#include "request.h"
#include "buffer.h"

#include <utility> // std::pair
#include <vector>

class SMO
{
public:
  typedef enum {
    SOURCE,
    CONSUMER,
    UNDEFINED,
  } Time_group;

  typedef std::pair<Time_group, unsigned> Min_time_t;
  typedef std::shared_ptr<Counter>        Counter_ptr;

  static void main_loop();

private:
  typedef std::vector<Source>   Sources;
  typedef std::vector<Consumer> Consumers;
  typedef Request::Request_ptr  Request_ptr;

  static Min_time_t find_min_time(const Sources   & sources,
                                  const Consumers & consumers);
  template < typename T >
  static unsigned find_min_time(const std::vector<T> & devices);

  static void print_calendar(const Sources     & sources,
                             const Consumers   & consumers,
                             const Buffer      & buffer,
                             const Counter_ptr & counter);
  static void print_result_table(const Sources     & sources,
                                 const Consumers   & consumers,
                                 const Counter_ptr & counter);
};

#endif // SMO_H
