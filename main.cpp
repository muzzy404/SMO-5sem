#include <QCoreApplication>

// first, your own headers
// next, other headers

#include "smo.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  SMO::main_loop();

  return a.exec();
}
