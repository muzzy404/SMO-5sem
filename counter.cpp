#include "counter.h"

#include <algorithm>

Counter::Counter(index_t sources_num, index_t consumers_num)
{
  total_     = std::vector<unsigned>(sources_num, 0);
  rejected_  = std::vector<unsigned>(sources_num, 0);
  processed_ = std::vector<unsigned>(consumers_num, 0);

  service_time_   = std::vector<time_t>(sources_num, 0.0);
  in_buffer_time_ = std::vector<time_t>(sources_num, 0.0);
  in_system_time_ = std::vector<time_t>(sources_num, 0.0);
  working_time_   = std::vector<time_t>(consumers_num, 0.0);

  in_buffer_time_pow_ = std::vector<time_t>(sources_num, 0.0);
  service_time_pow_   = std::vector<time_t>(sources_num, 0.0);
}

void Counter::add_service_time(index_t i, const time_t delta)
{
  service_time_[i]     += delta;
  service_time_pow_[i] += (delta * delta);
}

void Counter::add_in_buffer_time(index_t i, const time_t delta)
{
  in_buffer_time_[i]     += delta;
  in_buffer_time_pow_[i] += (delta * delta);
}

void Counter::add_in_system_time(index_t i, const time_t delta)
{
  in_system_time_[i] += delta;
}

void Counter::add_working_time(index_t i, const time_t delta)
{
  working_time_[i] += delta;
}

unsigned Counter::total() const
{
  unsigned total = 0;

  for(unsigned num : total_) {
    total += num;
  }
  return total;
}

unsigned Counter::processed() const
{
  return std::accumulate(processed_.begin(),
                         processed_.end(), 0);
}

unsigned Counter::rejected() const
{
  return std::accumulate(rejected_.begin(),
                         rejected_.end(), 0);
}


double Counter::get_rejection_probability(index_t i) const
{
  if (total_.at(i) != 0)
    return 100 * ((double)rejected_[i] / total_[i]);

  return 0.0;
}

double Counter::get_waiting_dispersion(index_t i) const
{
  unsigned total   = total_[i];
  double   average = in_buffer_time_[i] / total;

  return ((in_buffer_time_pow_[i] / total) - (average * average));
}

double Counter::get_service_dispersion(index_t i) const
{
  unsigned total   = total_[i];
  double   average = service_time_[i] / total;

  return ((service_time_pow_[i] / total) - (average * average));
}

Counter::time_t Counter::get_waiting_time(index_t i) const
{
  return (in_buffer_time_[i] / total_[i]);
}

Counter::time_t Counter::get_service_time(index_t i) const
{
  return (service_time_[i] / total_[i]);
}

Counter::time_t Counter::get_in_system_time(index_t i) const
{
  return (in_system_time_[i] / total_[i]);
}

double Counter::count_consumers_coeff(const index_t i,
                                      const time_t realisation_time) const
{
  return (working_time_[i] / realisation_time);
}
