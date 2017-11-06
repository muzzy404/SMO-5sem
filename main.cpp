#include "system.h"
//#include "mainwindow.h"
#include "stepbystepwindow.h"

//#include <cstdio> // getchar()
#include <memory>   // shared_ptr

//#include <QCoreApplication>
#include <QApplication>

int main(int argc, char *argv[])
{
  // console test
  /*QCoreApplication a(argc, argv);

  System smo;
  smo.print_calendar();

  while (!smo.finished()) {
    std::getchar();
    smo.next_iteration();
    smo.print_calendar();
  }

  std::getchar();
  smo.print_result_table();*/


  QApplication a(argc, argv);

  // main window test
  /*MainWindow w;
  w.show();*/

  auto smo = std::make_shared<System>();

  StepByStepWindow w(smo);
  w.show();

  return a.exec();
}
