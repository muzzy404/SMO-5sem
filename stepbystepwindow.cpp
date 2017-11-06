#include "stepbystepwindow.h"
#include "ui_stepbystepwindow.h"

#include <QString>
#include <QMessageBox>

StepByStepWindow::StepByStepWindow(System_ptr & system,
                                   QWidget * parent) :
  QWidget(parent),
  ui(new Ui::StepByStepWindow)
{
  ui->setupUi(this);

  system_ = system;

  ui->tblSources->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tblBuffer->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tblConsumers->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  ui->tblSources->setRowCount(system_->get_sources_num());
  ui->tblBuffer->setRowCount(system_->get_buffer_size());
  ui->tblConsumers->setRowCount(system_->get_consumers_num());

  ui->modelingProgressBar->setValue(0);

  connect(ui->btnNext, SIGNAL (released()), this, SLOT (btn_next_pressed()));

  update_visible_data();
}

StepByStepWindow::~StepByStepWindow()
{
  delete ui;
}

void StepByStepWindow::btn_next_pressed()
{
  try {
    system_->next_iteration();
    update_visible_data();
  } catch (...) {
    QMessageBox msg;
    msg.setText("Simulation has been completed.");
    msg.exec();
  }
}

void StepByStepWindow::update_visible_data()
{
  System::devices_state_t sources = system_->get_sources_state();
  for(unsigned i = 0; i < system_->get_sources_num(); ++i) {
    QString time = QString::fromStdString(sources.at(i).first);
    QString req  = QString::fromStdString(sources.at(i).second);

    ui->tblSources->setItem(i, 0, new QTableWidgetItem(time));
    ui->tblSources->setItem(i, 1, new QTableWidgetItem(req));
  }

  System::devices_state_t consumers = system_->get_consumers_state();
  for(unsigned i = 0; i < system_->get_consumers_num(); ++i) {
    QString time = QString::fromStdString(consumers.at(i).first);
    QString req  = QString::fromStdString(consumers.at(i).second);

    ui->tblConsumers->setItem(i, 0, new QTableWidgetItem(time));
    ui->tblConsumers->setItem(i, 1, new QTableWidgetItem(req));
  }

  System::buffer_state_t buffer = system_->get_buffer_state();
  for(unsigned i = 0; i < system_->get_buffer_size(); ++i) {
    QString req = QString::fromStdString(buffer.at(i));

    ui->tblBuffer->setItem(i, 0, new QTableWidgetItem(req));
  }

  ui->modelingProgressBar->setValue(system_->get_progress());
}
