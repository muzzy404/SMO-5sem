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

  void start();

private slots:
  void btn_next_pressed(const bool update = true);

private:
  Ui::StepByStepWindow * ui;

  System_ptr system_;

  void update_visible_data();
  void update_counters();

  //TODO: void closeEvent();

  const unsigned lim_for_updates = 9999;
};

#endif // STEPBYSTEPWINDOW_H
