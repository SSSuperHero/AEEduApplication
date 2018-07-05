#include "headcontrolwidget.h"
#include "ui_headcontrolwidget.h"

HeadControlWidget::HeadControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeadControlWidget)
{
    ui->setupUi(this);
}

HeadControlWidget::~HeadControlWidget()
{
    delete ui;
}
