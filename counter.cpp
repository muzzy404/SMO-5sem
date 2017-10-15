#include "counter.h"

Counter::Counter(index_t size)
{
  total_    = std::vector<unsigned>(size, 0);
  rejected_ = std::vector<unsigned>(size, 0);

  service_time_   = std::vector<time_t>(size, 0.0);
  in_buffer_time_ = std::vector<time_t>(size, 0.0);
  in_system_time_ = std::vector<time_t>(size, 0.0);

  in_buffer_time_pow_ = std::vector<time_t>(size, 0.0);
  service_time_pow_   = std::vector<time_t>(size, 0.0);
}

void Counter::add_service_time(index_t i, const time_t delta)
{
  service_time_[i]     += delta;
  service_time_pow_[i] += delta * delta;
}

void Counter::add_in_buffer_time(index_t i, const time_t delta)
{
  in_buffer_time_[i]     += delta;
  in_buffer_time_pow_[i] += delta * delta;
}

void Counter::add_in_system_time(index_t i, const time_t delta)
{
  in_system_time_[i] += delta;
}

unsigned Counter::get_total() const
{
  unsigned total = 0;
  for(unsigned num : total_)
  {
    total += num;
  }
  return total;
}

double Counter::get_rejection_probability(index_t i) const
{
  return (rejected_[i] / total_[i]);
}

double Counter::get_waiting_dispersion(index_t i) const
{
  auto total = total_[i];
  return ((in_buffer_time_pow_[i] / total) -
          (in_buffer_time_[i]     / total));
}

double Counter::get_service_dispersion(index_t i) const
{
  auto total = total_[i];
  return ((service_time_pow_[i] / total) -
          (service_time_[i]     / total));
}

Counter::time_t Counter::get_waiting_time(index_t i) const
{
  return (in_buffer_time_[i] / total_[i]);
}

Counter::time_t Counter::get_service_time(index_t i) const
{
  return (service_time_[i] / total_[i]);
}

Counter::time_t Counter::count_device_coeff(const time_t device_time,
                                            const time_t total_time) const
{
  return (device_time / total_time);
}
