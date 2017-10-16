#ifndef COUNTER_H
#define COUNTER_H

#include <vector>
#include <memory>  // std::chared_ptr

class Counter
{
public:
  typedef const unsigned           index_t;
  typedef double                   time_t;
  typedef std::shared_ptr<Counter> Counter_ptr;

  Counter(index_t sources_num);

  unsigned size() const { return total_.size(); }

  void add_request(index_t i)  { total_[i] += 1;    }
  void add_rejected(index_t i) { rejected_[i] += 1; }

  void add_service_time(index_t i, const time_t delta);
  void add_in_buffer_time(index_t i, const time_t delta);
  void add_in_system_time(index_t i, const time_t delta);

  unsigned total()             const;
  unsigned total(index_t i)    const { return total_[i];    }
  unsigned rejected(index_t i) const { return rejected_[i]; }

  double get_rejection_probability(index_t i) const;
  double get_waiting_dispersion(index_t i)    const;
  double get_service_dispersion(index_t i)    const;

  time_t get_waiting_time(index_t i)   const;
  time_t get_service_time(index_t i)   const;
  time_t get_in_system_time(index_t i) const;

  time_t count_device_coeff(const time_t device_time,
                            const time_t realisation_time) const;

private:
  typedef std::vector<unsigned> statistics_num;
  typedef std::vector<double>   statistics_time;

  statistics_num total_;
  statistics_num rejected_;

  statistics_time service_time_;
  statistics_time in_buffer_time_;
  statistics_time in_system_time_;

  statistics_time in_buffer_time_pow_;
  statistics_time service_time_pow_;
};

#endif // COUNTER_H
