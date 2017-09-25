#ifndef CONSTANTS_H
#define CONSTANTS_H


class Constants
{
private:
  static const int ALPHA_DEFAULT = 1;
  static const int BETA_DEFAULT  = 2;

  static int alpha_;
  static int beta_;

public:
  static void reset_all();

  static int get_alpha() { return alpha_; }
  static int get_beta()  { return beta_;  }


  static void set_alpha(int alpha) { alpha_ = alpha; }
  static void set_beta(int beta)   { beta_  = beta;  }

};

#endif // CONSTANTS_H
