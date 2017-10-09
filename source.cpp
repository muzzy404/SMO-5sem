#include "source.h"
#include "constants.h"

//#include <cstdlib> for std::rand()

Source::Source(const long priority) :
  priority_(priority), current_time_(0.0)
{}

double Source::delta_time() const
{
  return 2;
}
