#include "stepbystepwindow.h"
#include "ui_stepbystepwindow.h"

#include <QStringList>

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
}

StepByStepWindow::~StepByStepWindow()
{
  delete ui;
}
