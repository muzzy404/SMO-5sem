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
  typedef Counter::statistics_num      statistics_num;
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

  statistics_num get_total_requests()    const { return counter_->statistics_total();     }
  statistics_num get_rejected_requests() const { return counter_->statistics_rejected();  }
  statistics_num get_total_processed()   const { return counter_->statistics_processed(); }

  typedef Counter::time_t          time_t;
  typedef std::vector<double>      statistics_t;
  typedef Counter::statistics_time statistics_time_t;

  // getters for results
  Counter::time_t get_realisation_time() const;

  void count_statistics();
  statistics_t rejection_probability() const { return rejection_probability_; }
  statistics_t devices_coeff()         const { return devices_coeff_; }
  statistics_t waiting_dispersion()    const { return waiting_dispersion_; }
  statistics_t service_dispersion()    const { return service_dispersion_; }

  statistics_time_t times_in_system() const { return counter_->statistics_in_system_time(); }
  statistics_time_t times_waiting() const { return counter_->statistics_waiting_time(); }
  statistics_time_t times_service() const { return counter_->statistics_service_time(); }
  statistics_time_t times_working() const { return counter_->statistics_working_time(); }

  unsigned total_reqs_num()     const { return counter_->total();     }
  unsigned processed_reqs_num() const { return counter_->processed(); }
  unsigned rejected_reqs_num()  const { return counter_->rejected();  }

  unsigned get_sources_num()   const { return sources_.size();   }
  unsigned get_buffer_size()   const { return buffer_->size();   }
  unsigned get_consumers_num() const { return consumers_.size(); }

  int get_progress() const;

  bool step_by_step_mode() const { return step_by_step_mode_; }
  std::string get_status() const { return status_; }
  unsigned get_max_requests() const { return max_requests_; }

  double average_rejection() const { return counter_->get_rejection_probability(); }

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

  const unsigned max_requests_;
  const bool     step_by_step_mode_;

  std::string status_;

  statistics_t rejection_probability_;
  statistics_t devices_coeff_;
  statistics_t waiting_dispersion_;
  statistics_t service_dispersion_;
};

#endif // SYSTEM_H
