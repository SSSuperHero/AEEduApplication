#include "topcontrolwidget.h"
#include "ui_topcontrolwidget.h"

TopControlWidget::TopControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TopControlWidget)
{
    ui->setupUi(this);
}

TopControlWidget::~TopControlWidget()
{
    delete ui;
}
