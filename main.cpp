#include <QCoreApplication>

// first, your own headers
// next, other headers

#include "request.h"
#include "buffer.h"

#include <iostream>
#include <memory>
#include <exception>

void test()
{
  auto counter = std::make_shared<Counter>(5);
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


int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  test();

  return a.exec();
}
