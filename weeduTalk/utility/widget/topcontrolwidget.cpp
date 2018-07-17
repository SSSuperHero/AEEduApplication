#include "topcontrolwidget.h"
#include "ui_topcontrolwidget.h"

TopControlWidget::TopControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TopControlWidget)
{
    ui->setupUi(this);

    ui->label_text->hide();
}

TopControlWidget::~TopControlWidget()
{
    delete ui;
}

void TopControlWidget::setShowText(const QString _text)
{

    if( _text.isEmpty() )
    {
        ui->pushButtonText->hide();
    }
    else
    {
        ui->pushButtonText->show();
    }

    ui->label_text->hide();
    ui->label_text->setText( _text );

}

void TopControlWidget::on_pushButton_clicked()
{
    emit signal_back();
}

void TopControlWidget::on_pushButtonText_clicked()
{

    if( ui->label_text->isVisible() )
    {
        ui->label_text->hide();
    }
    else
    {
        ui->label_text->show();
    }
}
