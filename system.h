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
  typedef std::vector<Device::state_t> devices_state_t;
  typedef Buffer::state_t              buffer_state_t;

  System();

  void next_iteration();

  bool finished() const { return finished_; }

  // TODO: remove
  void print_calendar()     const;
  void print_result_table() const;

  // getters for calendar
  buffer_state_t  get_buffer_state()    const;
  devices_state_t get_sources_state()   const;
  devices_state_t get_consumers_state() const;

  // getters for results
  Counter::Counter_ptr get_counter() const { return counter_; }
  std::vector<double>  get_devices_coeff() const;

  unsigned get_sources_num()   const { return sources_.size();   }
  unsigned get_buffer_size()   const { return buffer_->size();   }
  unsigned get_consumers_num() const { return consumers_.size(); }

  int get_progress() const;

  bool step_by_step_mode() const { return step_by_step_mode_; }

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

  const unsigned min_requests_;
  const bool     step_by_step_mode_;
};

#endif // SYSTEM_H
