#include "topcontrolwidget.h"
#include "ui_topcontrolwidget.h"

TopControlWidget::TopControlWidget(QWidget *parent) :
    BaseWidget(parent),
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

void TopControlWidget::setChooseLesson(const int _lessonNum, const int _curIndex)
{
    clearLayout( ui->horizontalLayout_chooseLesson );

    for( int i = 0; i < _lessonNum; i++ )
    {
        QPushButton *_btn = new QPushButton(this);
        _btn->setText( QString::number( i+1 ) );

        if( i == _curIndex )
        {
            _btn->setStyleSheet("border-image: url(:/images/courseNumOn.png);");
        }
        else
        {
            _btn->setStyleSheet("border-image: url(:/images/courseNumOff.png);");
        }
    }
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
