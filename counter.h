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

  typedef std::vector<unsigned> statistics_num;
  typedef std::vector<time_t>   statistics_time;

  Counter(index_t sources_num, index_t consumers_num);

  unsigned size_src()  const { return total_.size(); }
  unsigned size_cnmr() const { return processed_.size(); }

  void add_request(index_t i)   { total_[i] += 1;    }
  void add_rejected(index_t i)  { rejected_[i] += 1; }
  void add_processed(index_t i) { processed_[i] += 1; }

  void add_service_time(index_t i, const time_t delta);
  void add_in_buffer_time(index_t i, const time_t delta);
  void add_in_system_time(index_t i, const time_t delta);
  void add_working_time(index_t i, const time_t delta);

  unsigned total()     const;
  unsigned processed() const;
  unsigned rejected()  const;

  unsigned total(index_t i)    const  { return total_[i];     }
  unsigned rejected(index_t i) const  { return rejected_[i];  }
  unsigned processed(index_t i) const { return processed_[i]; }
  statistics_num statistics_total()     const { return total_;     }
  statistics_num statistics_rejected()  const { return rejected_;  }
  statistics_num statistics_processed() const { return processed_; }

  double get_rejection_probability()          const;
  double get_rejection_probability(index_t i) const;
  double get_waiting_dispersion(index_t i)    const;
  double get_service_dispersion(index_t i)    const;

  time_t get_waiting_time(index_t i)   const;
  time_t get_service_time(index_t i)   const;
  time_t get_in_system_time(index_t i) const;
  statistics_time statistics_service_time()   const;// { return service_time_; }
  statistics_time statistics_working_time()   const { return working_time_; }
  statistics_time statistics_waiting_time()   const;// { return in_buffer_time_; }
  statistics_time statistics_in_system_time() const;// { return in_system_time_; }

  double count_consumers_coeff(const index_t i,
                               const time_t realisation_time) const;

private:
  statistics_num total_;
  statistics_num rejected_;
  statistics_num processed_;

  statistics_time service_time_;
  statistics_time in_buffer_time_;
  statistics_time in_system_time_;
  statistics_time working_time_;

  statistics_time in_buffer_time_pow_;
  statistics_time service_time_pow_;
};

#endif // COUNTER_H
