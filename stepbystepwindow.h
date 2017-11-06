#ifndef STEPBYSTEPWINDOW_H
#define STEPBYSTEPWINDOW_H

#include "system.h"

#include <memory> // shared_ptr

#include <QWidget>

namespace Ui {
  class StepByStepWindow;
}

class StepByStepWindow : public QWidget
{
  Q_OBJECT

public:
  typedef std::shared_ptr<System> System_ptr;

  explicit StepByStepWindow(System_ptr & system,
                            QWidget * parent = 0);
  ~StepByStepWindow();



private:
  Ui::StepByStepWindow *ui;

  System_ptr system_;
};

#endif // STEPBYSTEPWINDOW_H