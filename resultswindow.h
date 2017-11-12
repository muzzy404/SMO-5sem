#ifndef RESULTSWINDOW_H
#define RESULTSWINDOW_H

#include <QWidget>

namespace Ui {
  class ResultsWindow;
}

class ResultsWindow : public QWidget
{
  Q_OBJECT

public:
  explicit ResultsWindow(QWidget *parent = 0);
  ~ResultsWindow();

private:
  Ui::ResultsWindow *ui;
};

#endif // RESULTSWINDOW_H
