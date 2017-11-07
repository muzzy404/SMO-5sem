#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdlib> // std::random

class Constants
{
public:
  static double alpha()           { return alpha_;        }
  static double beta()            { return beta_;         }
  static double lambda()          { return lambda_;       }
  static unsigned sources()       { return sources_;      }
  static unsigned consumers()     { return consumers_;    }
  static unsigned buffer()        { return buffer_;       }
  static unsigned min_requests()  { return min_requests_; }
  static bool step_by_step_mode() { return step_by_step_mode_; }

  static void set_alpha(double alpha)          { alpha_     = alpha;  }
  static void set_beta(double beta)            { beta_      = beta;   }
  static void set_lambda(double lambda)        { lambda_    = lambda; }
  static void set_sources(unsigned num)        { sources_   = num;    }
  static void set_consumers(unsigned num)      { consumers_ = num;    }
  static void set_buffer(unsigned size)        { buffer_    = size;   }
  static void set_min_requests(unsigned num)   { min_requests_ = num; }
  static void set_step_by_step_mode(bool mode) { step_by_step_mode_ = mode; }

  static void reset_all();

  static double distribution() {
    return (double)std::rand() / RAND_MAX;
  }

private:
  static constexpr double   ALPHA_DEFAULT         = 1.0;
  static constexpr double   BETA_DEFAULT          = 3.0;
  static constexpr double   LAMBDA_DEFAULT        = 0.2;
  static constexpr unsigned SOURCES_DEFAULT       = 12;
  static constexpr unsigned CONSUMERS_DEFAULT     = 7;
  static constexpr unsigned BUFFER_DEFAULT        = 6;
  static constexpr unsigned MIN_REQUESTS_DEFAULT  = 100;
  static constexpr bool STEP_BY_STEP_MODE_DEFAULT = true;

  static double   alpha_;
  static double   beta_;
  static double   lambda_;
  static unsigned sources_;
  static unsigned consumers_;
  static unsigned buffer_;
  static unsigned min_requests_;
  static bool     step_by_step_mode_;
};

#endif // CONSTANTS_H
