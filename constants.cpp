#include "constants.h"

double Constants::alpha_  = Constants::ALPHA_DEFAULT;
double Constants::beta_   = Constants::BETA_DEFAULT;
double Constants::lambda_ = Constants::LAMBDA_DEFAULT;

unsigned Constants::sources_      = Constants::SOURCES_DEFAULT;
unsigned Constants::consumers_    = Constants::CONSUMERS_DEFAULT;
unsigned Constants::buffer_       = Constants::BUFFER_DEFAULT;
unsigned Constants::min_requests_ = Constants::MIN_REQUESTS_DEFAULT;

void Constants::reset_all() {
  alpha_        = ALPHA_DEFAULT;
  beta_         = BETA_DEFAULT;
  lambda_       = LAMBDA_DEFAULT;
  sources_      = SOURCES_DEFAULT;
  consumers_    = CONSUMERS_DEFAULT;
  buffer_       = BUFFER_DEFAULT;
  min_requests_ = MIN_REQUESTS_DEFAULT;
}

