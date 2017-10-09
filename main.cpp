#include <QCoreApplication>

// first, your own headers
// next, other headers

#include "request.h"
#include "buffer.h"

#include <iostream>
#include <memory>


void test()
{
  Buffer buffer(5);

  buffer.add(std::make_shared<Request>(3, 2, 55.05));
  buffer.add(std::make_shared<Request>(2, 2, 56.05));
  buffer.add(std::make_shared<Request>(1, 3, 55.05));
  buffer.add(std::make_shared<Request>(2, 3, 55.05));
  buffer.add(std::make_shared<Request>(3, 3, 55.05));
  buffer.add(std::make_shared<Request>(55, 66, 55.05));

  buffer.print_reqs();

  auto req = buffer.get();
  std::cout << "min: " << req->get_priority() << "." << req->get_number() << "\n\n";

  buffer.print_reqs();

  req = buffer.get();
  std::cout << "\nmin: " << req->get_priority() << "." << req->get_number() << "\n\n";

  buffer.print_reqs();

  std::cout << "\nend of test\n\n";

}


int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  test();

  return a.exec();
}
