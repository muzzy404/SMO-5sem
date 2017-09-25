#include "constants.h"

int Constants::alpha_ = Constants::ALPHA_DEFAULT;
int Constants::beta_  = Constants::BETA_DEFAULT;

void Constants::reset_all()
{
  alpha_ = ALPHA_DEFAULT;
  beta_  = BETA_DEFAULT;
}
