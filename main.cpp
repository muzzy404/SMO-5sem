#include <QCoreApplication>
//#include <QApplication>

#include "smo.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  SMO::main_loop();

  /*QApplication a(argc, argv);

  MainWindow w;
  w.show();*/

  return a.exec();
}
