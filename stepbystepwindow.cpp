#include "stepbystepwindow.h"
#include "ui_stepbystepwindow.h"

#include "resultswindow.h"

#include <QString>
#include <QMessageBox>

StepByStepWindow::StepByStepWindow(const System_ptr & system,
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

  connect(ui->btnOpenResults, SIGNAL (released()),
          this, SLOT (btn_open_results_pressed()));

  update_visible_data();
}

StepByStepWindow::~StepByStepWindow()
{
  delete ui;
}

void StepByStepWindow::start()
{
  QMessageBox msg;
  msg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
  msg.setText("Press Ok to start simulation");
  msg.exec();

  if (!system_->step_by_step_mode()) {
    while (!system_->finished()) {

      // limit for visual updating
      if (system_->get_max_requests() > lim_for_updates) {
        int progress = system_->get_progress();
        if (progress % 10 != 0 && progress != 99) {
          btn_next_pressed(false);
          continue;
        }
      }

      // regular case
      btn_next_pressed();
    }
    // to open msgBox
    btn_next_pressed();
  }

}

void StepByStepWindow::btn_next_pressed(const bool update)
{
  try {
    system_->next_iteration();
    if (update)
      update_visible_data();
  } catch (...) {
    QMessageBox msg;
    msg.setText("Simulation has been completed.");
    msg.exec();

    ui->btnNext->setEnabled(false);
    ui->btnOpenResults->setEnabled(true);
  }
}

void StepByStepWindow::btn_open_results_pressed()
{
  system_->count_statistics();
  ResultsWindow * results_window = new ResultsWindow(system_);
  results_window->show();
}

void StepByStepWindow::update_visible_data()
{
  if (!system_->step_by_step_mode()) {
    ui->btnNext->setEnabled(false);
  }

  System::devices_state_t sources = system_->get_sources_state();
  System::statistics_num all_total    = system_->get_total_requests();
  System::statistics_num all_rejected = system_->get_rejected_requests();

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

  System::devices_state_t consumers    = system_->get_consumers_state();
  System::statistics_num all_processed = system_->get_total_processed();

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
  QString generated = QString::number(system_->total_reqs_num()) + "/" +
                      QString::number(system_->get_max_requests());
  auto processed = system_->processed_reqs_num();
  auto rejected  = system_->rejected_reqs_num();
  auto sum = processed + rejected;

  ui->lblGenField->setText(generated);

  ui->lblProcField->setText(QString::number(processed));
  ui->lblRejField->setText(QString::number(rejected));
  ui->lblTotalField->setText(QString::number(sum));
}
