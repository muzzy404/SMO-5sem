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

  connect(ui->btnNext, SIGNAL (released()),
          this, SLOT (btn_next_pressed()));


  update_visible_data();

  // TODO: move to separete function
  if (!system_->step_by_step_mode()) {
    while (!system_->finished()) {
      btn_next_pressed();
    }
    return;
  }
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

    ui->btnNext->setEnabled(false);
    ui->btnOpenResults->setEnabled(true);
  }
}

void StepByStepWindow::update_visible_data()
{
  System::devices_state_t sources = system_->get_sources_state();
  System::amount_t all_total      = system_->get_total_requests();
  System::amount_t all_rejected   = system_->get_rejected_requests();

  for(unsigned i = 0; i < system_->get_sources_num(); ++i) {
    QString time = QString::fromStdString(sources.at(i).first);
    QString req  = QString::fromStdString(sources.at(i).second);

    QString total    = QString::number(all_total.at(i));
    QString rejected = QString::number(all_rejected.at(i));

    ui->tblSources->setItem(i, 0, new QTableWidgetItem(time));
    ui->tblSources->setItem(i, 1, new QTableWidgetItem(req));
    ui->tblSources->setItem(i, 2, new QTableWidgetItem(rejected));
    ui->tblSources->setItem(i, 3, new QTableWidgetItem(total));
  }

  System::devices_state_t consumers = system_->get_consumers_state();
  System::amount_t all_processed = system_->get_total_processed();

  for(unsigned i = 0; i < system_->get_consumers_num(); ++i) {
    QString time = QString::fromStdString(consumers.at(i).first);
    QString req  = QString::fromStdString(consumers.at(i).second);
    QString processed = QString::number(all_processed.at(i));

    ui->tblConsumers->setItem(i, 0, new QTableWidgetItem(time));
    ui->tblConsumers->setItem(i, 1, new QTableWidgetItem(req));
    ui->tblConsumers->setItem(i, 2, new QTableWidgetItem(processed));
  }

  System::buffer_state_t buffer = system_->get_buffer_state();
  for(unsigned i = 0; i < system_->get_buffer_size(); ++i) {
    QString req = QString::fromStdString(buffer.at(i));

    ui->tblBuffer->setItem(i, 0, new QTableWidgetItem(req));
  }

  ui->modelingProgressBar->setValue(system_->get_progress());
  ui->lblStatusBar->setText(QString::fromStdString(system_->get_status()));

  update_counters();
}

void StepByStepWindow::update_counters()
{
  auto counter = system_->get_counter();
  QString generated = QString::number(counter->total()) + "/" +
                      QString::number(system_->get_max_requests());
  auto processed = counter->processed();
  auto rejected  = counter->rejected();
  auto sum = processed + rejected;

  ui->lblGenField->setText(generated);

  ui->lblProcField->setText(QString::number(processed));
  ui->lblRejField->setText(QString::number(rejected));
  ui->lblTotalField->setText(QString::number(sum));
}
