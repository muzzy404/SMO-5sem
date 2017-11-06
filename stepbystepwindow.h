#ifndef STEPBYSTEPWINDOW_H
#define STEPBYSTEPWINDOW_H

#include <QWidget>

namespace Ui {
  class StepByStepWindow;
}

class StepByStepWindow : public QWidget
{
  Q_OBJECT

public:
  explicit StepByStepWindow(unsigned, unsigned, unsigned,
                            QWidget * parent = 0);
  ~StepByStepWindow();



private:
  Ui::StepByStepWindow *ui;
};

#endif // STEPBYSTEPWINDOW_H
