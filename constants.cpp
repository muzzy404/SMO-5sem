#include "constants.h"

double Constants::alpha_  = Constants::ALPHA_DEFAULT;
double Constants::beta_   = Constants::BETA_DEFAULT;
double Constants::lambda_ = Constants::LAMBDA_DEFAULT;

void Constants::reset_all() {
  alpha_  = ALPHA_DEFAULT;
  beta_   = BETA_DEFAULT;
  lambda_ = LAMBDA_DEFAULT;
}

