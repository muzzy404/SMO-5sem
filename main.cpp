#include "system.h"
//#include "mainwindow.h"
#include "stepbystepwindow.h"

#include <cstdio> // getchar()

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

  StepByStepWindow w(10, 25, 8);
  w.show();

  return a.exec();
}
