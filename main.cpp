#include "system.h"

#include "mainwindow.h"
//#include "stepbystepwindow.h"

//#include <memory>   // shared_ptr

//#include <QCoreApplication>
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  // main window test
  MainWindow w;
  w.show();

//  auto smo = std::make_shared<System>();

//  StepByStepWindow step_by_step_w(smo);
//  step_by_step_w.show();

  return a.exec();
}
