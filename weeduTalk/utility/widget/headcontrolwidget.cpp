#include "headcontrolwidget.h"
#include "ui_headcontrolwidget.h"

HeadControlWidget::HeadControlWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::HeadControlWidget)
{
    ui->setupUi(this);

    reSetSize( ui->pushButtonMin );
    reSetSize( ui->pushButton_max );
    reSetSize( ui->pushButton_close);
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
