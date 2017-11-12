#include "resultswindow.h"
#include "ui_resultswindow.h"

#include <QString>

ResultsWindow::ResultsWindow(const System_ptr & system,
                             QWidget * parent) :
  QWidget(parent),
  ui(new Ui::ResultsWindow)
{
  ui->setupUi(this);

  system_ = system;

  ui->tblRejection->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tblTime->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tblDispersion->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tblConsumers->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  show_data();
}

ResultsWindow::~ResultsWindow()
{
  delete ui;
}

void ResultsWindow::show_data()
{
  QString realisation_time = QString::number(system_->get_realisation_time(), 'f',
                                             PRECISION);
  ui->lblRealisationTimeField->setText(realisation_time);

  // table 1
  auto n_total_reqs_all    = system_->get_total_requests();
  auto n_rejected_reqs_all = system_->get_rejected_requests();
  auto p_rejection_all     = system_->rejection_probability();

  // table 2
  auto t_in_system_all = system_->times_in_system();
  auto t_waiting_all   = system_->times_waiting();
  auto t_service_all   = system_->times_service();

  // table 3
  auto d_waiting_all = system_->waiting_dispersion();
  auto d_service_all = system_->service_dispersion();

  // table 4
  auto t_working_all = system_->times_working();
  auto c_working_all = system_->devices_coeff();

  const int sources_rows   = n_total_reqs_all.size();
  ui->tblRejection->setRowCount(sources_rows);
  ui->tblTime->setRowCount(sources_rows);
  ui->tblDispersion->setRowCount(sources_rows);

  for (int i = 0; i < sources_rows; ++i) {
    QString n_total     = QString::number(n_total_reqs_all.at(i));
    QString n_rejected  = QString::number(n_rejected_reqs_all.at(i));
    QString p_rejection = QString::number(p_rejection_all.at(i), 'f', 2) + "%";

    QString t_in_system = QString::number(t_in_system_all.at(i), 'f', PRECISION);
    QString t_waiting   = QString::number(t_waiting_all.at(i), 'f', PRECISION);
    QString t_service   = QString::number(t_service_all.at(i), 'f', PRECISION);

    QString d_waiting = QString::number(d_waiting_all.at(i), 'g', PRECISION);
    QString d_service = QString::number(d_service_all.at(i), 'g', PRECISION);

    ui->tblRejection->setItem(i, 0, new QTableWidgetItem(n_total));
    ui->tblRejection->setItem(i, 1, new QTableWidgetItem(n_rejected));
    ui->tblRejection->setItem(i, 2, new QTableWidgetItem(p_rejection));

    ui->tblTime->setItem(i, 0, new QTableWidgetItem(t_in_system));
    ui->tblTime->setItem(i, 1, new QTableWidgetItem(t_waiting));
    ui->tblTime->setItem(i, 2, new QTableWidgetItem(t_service));

    ui->tblDispersion->setItem(i, 0, new QTableWidgetItem(d_waiting));
    ui->tblDispersion->setItem(i, 1, new QTableWidgetItem(d_service));
  }

  const int consumers_rows = t_working_all.size();
  ui->tblConsumers->setRowCount(consumers_rows);

  for (int i = 0; i < consumers_rows; ++i) {
    QString t_working = QString::number(t_working_all.at(i), 'f', PRECISION);
    QString c_working = QString::number(c_working_all.at(i), 'f', PRECISION);

    ui->tblConsumers->setItem(i, 0, new QTableWidgetItem(t_working));
    ui->tblConsumers->setItem(i, 1, new QTableWidgetItem(c_working));
  }
}
