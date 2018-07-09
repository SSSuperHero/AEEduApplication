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

void HeadControlWidget::on_pushButtonMin_clicked()
{
    emit signal_widgetMin();
}

void HeadControlWidget::on_pushButton_max_clicked()
{
    emit signal_widgetMax();
}

void HeadControlWidget::on_pushButton_close_clicked()
{
    emit signal_widgetClose();
}
