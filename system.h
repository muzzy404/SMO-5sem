#ifndef SYSTEM_H
#define SYSTEM_H

#include <counter.h>
#include <buffer.h>
#include <source.h>
#include <consumer.h>

#include <memory.h> // std::unique_ptr

class System
{
public:
  System();

  void next_iteration();

  bool finished() const { return finished_; }

  void print_calendar()     const;
  void print_result_table() const;

  // TODO: getters for calendar

  // TODO: getters for results

private:
  typedef std::vector<Source>   Sources;
  typedef std::vector<Consumer> Consumers;

  typedef enum {
    SOURCE,
    CONSUMER,
  } devices_group;

  template < typename T >
  unsigned find_min_time(const std::vector<T> & devices) const;
  unsigned find_min_source()   const;
  unsigned find_min_consumer() const;

  Counter::Counter_ptr    counter_;
  std::unique_ptr<Buffer> buffer_;

  Sources   sources_;
  Consumers consumers_;

  bool process_rest_ = false;
  bool finished_     = false;

};

#endif // SYSTEM_H
