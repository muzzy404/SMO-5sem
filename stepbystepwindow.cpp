#include "stepbystepwindow.h"
#include "ui_stepbystepwindow.h"

#include <QStringList>

StepByStepWindow::StepByStepWindow(unsigned src,
                                   unsigned cnmr,
                                   unsigned buffer,
                                   QWidget * parent) :
  QWidget(parent),
  ui(new Ui::StepByStepWindow)
{
  ui->setupUi(this);

  ui->tblSources->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tblBuffer->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tblConsumers->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  ui->tblSources->setRowCount(src);
  ui->tblBuffer->setRowCount(buffer);
  ui->tblConsumers->setRowCount(cnmr);

  ui->modelingProgressBar->setValue(0);

}

StepByStepWindow::~StepByStepWindow()
{
  delete ui;
}
