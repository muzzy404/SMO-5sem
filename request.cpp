#include "request.h"
#include "counter.h"

#include <iostream>

Request::Request(unsigned priority, unsigned number, double time) :
  priority_(priority),
  number_(number),
  creation_time_(time)
{}

Request::~Request()
{
  std::cout << "deletion of " << this->get_priority()
            << "." << this->get_number() << "\n";
}
