#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "constants.h"
#include "stepbystepwindow.h"

#include <memory>

MainWindow::MainWindow(QWidget * parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->btnStart, SIGNAL (released()),
          this, SLOT (btn_start_pressed()));

  connect(ui->actionDefaultSettings, SIGNAL (triggered()),
          this, SLOT (reset_settings()));


  set_current_constants_to_fields();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::load_constants_to_settings()
{
  Constants::set_sources(ui->spinSrcs->value());
  Constants::set_consumers(ui->spinCnmrs->value());
  Constants::set_buffer(ui->spinBuffer->value());
  Constants::set_min_requests(ui->spinReqs->value());

  Constants::set_alpha(ui->spinAlpha->value());
  Constants::set_beta(ui->spinBeta->value());
  Constants::set_lambda(ui->spinLambda->value());

  Constants::set_step_by_step_mode(ui->chkBoxStepByStep->isChecked());
}

void MainWindow::set_current_constants_to_fields()
{
  ui->spinSrcs->setValue(Constants::sources());
  ui->spinCnmrs->setValue(Constants::consumers());
  ui->spinBuffer->setValue(Constants::buffer());
  ui->spinReqs->setValue(Constants::min_requests());

  ui->spinAlpha->setValue(Constants::alpha());
  ui->spinBeta->setValue(Constants::beta());
  ui->spinLambda->setValue(Constants::lambda());

  ui->chkBoxStepByStep->setChecked(Constants::step_by_step_mode());
}

void MainWindow::reset_settings()
{
  Constants::reset_all();
  set_current_constants_to_fields();
}

void MainWindow::btn_start_pressed()
{
  load_constants_to_settings();

  auto smo = std::make_shared<System>();

  StepByStepWindow * step_by_step_window = new StepByStepWindow(smo);
  step_by_step_window->show();
  step_by_step_window->start();
}
