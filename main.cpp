#include "system.h"
//#include "mainwindow.h"

#include <cstdio> // getchar()

#include <QCoreApplication>
//#include <QApplication>

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  //SMO::main_loop();

  System smo;
  smo.print_calendar();

  while (!smo.finished()) {
    std::getchar();
    smo.next_iteration();
    smo.print_calendar();
  }

  std::getchar();
  smo.print_result_table();

  /*QApplication a(argc, argv);

  MainWindow w;
  w.show();*/

  return a.exec();
}
