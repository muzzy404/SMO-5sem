#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget * parent = 0);
  ~MainWindow();

private slots:
  void btn_start_pressed();

private:
  Ui::MainWindow * ui;

  void load_constants_to_settings();
  void set_current_constants_to_fields();
};

#endif // MAINWINDOW_H
