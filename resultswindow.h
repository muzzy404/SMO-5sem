#ifndef RESULTSWINDOW_H
#define RESULTSWINDOW_H

#include "system.h"

#include <memory> // shared_ptr

#include <QWidget>

namespace Ui {
  class ResultsWindow;
}

class ResultsWindow : public QWidget
{
  Q_OBJECT

public:
  typedef std::shared_ptr<System> System_ptr;

  explicit ResultsWindow(const System_ptr & system,
                         QWidget * parent = 0);
  ~ResultsWindow();

private:
  Ui::ResultsWindow * ui;

  System_ptr system_;

  const int PRECISION = 4;

  void show_data();
};

#endif // RESULTSWINDOW_H
