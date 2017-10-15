#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdlib> // std::random

class Constants
{
private:
  static constexpr double ALPHA_DEFAULT  = 1.0;
  static constexpr double BETA_DEFAULT   = 3.0;
  static constexpr double LAMBDA_DEFAULT = 0.2;

  static double alpha_;
  static double beta_;
  static double lambda_;

public:
  static double get_alpha()  { return alpha_;  }
  static double get_beta()   { return beta_;   }
  static double get_lambda() { return lambda_; }

  static void reset_all();

  static double distribution() {
    return (double)std::rand() / RAND_MAX;
  }

  static void set_alpha(double alpha)   { alpha_  = alpha;  }
  static void set_beta(double beta)     { beta_   = beta;   }
  static void set_lambda(double lambda) { lambda_ = lambda; }
};

#endif // CONSTANTS_H
