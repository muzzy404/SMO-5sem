#include <QCoreApplication>

// first, your own headers
// next, other headers

#include "request.h"
#include "buffer.h"
#include "constants.h"

//TODO: remove extra later
#include <iostream>
#include <memory>
#include <exception>
#include <cstdlib>   // for random
#include <ctime>     // for random
#include <cmath>     // for log
#include <algorithm> // sort

void test()
{
  std::shared_ptr<Counter> counter = std::make_shared<Counter>(5);
  Buffer buffer(counter->size(), counter);

  buffer.add(std::make_shared<Request>(1, 4, 8.05));
  buffer.add(std::make_shared<Request>(1, 5, 9.15));
  buffer.add(std::make_shared<Request>(1, 2, 3.05));
  buffer.add(std::make_shared<Request>(1, 3, 6.05));
  buffer.add(std::make_shared<Request>(1, 1, 1.05));
  buffer.add(std::make_shared<Request>(55, 66, 55.05));

  buffer.print_reqs();

  auto req = buffer.get();
  std::cout << "min: " << req->get_priority() << "." << req->get_number() << "\n\n";

  buffer.print_reqs();

  req = buffer.get();
  std::cout << "\nmin: " << req->get_priority() << "." << req->get_number() << "\n\n";

  buffer.print_reqs();

  std::cout << "\n\nget 3 reqs\n\n";

  buffer.get();
  buffer.get();
  buffer.get();

  buffer.print_reqs();

  std::cout << "\n\nget from empty buffer\n";

  try {
    buffer.get();
  } catch (std::exception & e) {
    std::cout << e.what() << "\n";
  }

  std::cout << "\nend of test\n\n";
}

void time_gen_test()
{
  std::vector<double> exp_vec;

  std::srand(unsigned(std::time(0)));

  for(int i = 0; i < 100; ++i) {
    double delta_eq  = Constants::distribution() *
                      (Constants::get_beta() - Constants::get_alpha())
                                             + Constants::get_alpha();
    double delta_exp = -(1.0 / Constants::get_lambda()) *
                       std::log(1.0 - Constants::distribution());

    std::cout << i << ": " << delta_eq << ",  " << delta_exp << "\n";

    exp_vec.push_back(delta_exp);
  }

  std::cout << "\n\n";
  std::sort(exp_vec.begin(), exp_vec.end());
  for(double num : exp_vec) {
    std::cout << num << "\n";
  }
}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  test();
  time_gen_test();

  return a.exec();
}
