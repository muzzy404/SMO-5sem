#include "request.h"

#include <iostream>

Request::Request(long priority, long number, double time) :
  priority_(priority),
  number_(number),
  creation_time_(time)
{}

Request::~Request()
{
  std::cout << "deletion of " << this->get_priority() << "." << this->get_number() << "\n";
}
