#ifndef SMO_H
#define SMO_H

#include "source.h"
#include "consumer.h"
#include "request.h"

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

  static void main_loop();

private:
  typedef std::vector<Source>   Sources;
  typedef std::vector<Consumer> Consumers;
  typedef Request::Request_ptr  Request_ptr;

  static Min_time_t find_min_time(const Sources   & sources,
                                  const Consumers & consumers);
};

#endif // SMO_H
