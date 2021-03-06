#include "selectitemwidget.h"
#include "ui_selectitemwidget.h"
#include <QDebug>

SelectItemWidget::SelectItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectItemWidget)
{
    ui->setupUi(this);
}

void SelectItemWidget::bindData(const QString _titleStr, const wetalkDataListItem _data )
{
    m_dataItemInfo = _data;

    ui->labelTitle->setText( _titleStr );
    ui->labelText->setText( _data.text );
    qDebug()<<"SelectItemWidget bindData text:"<<_data.text;
}

void SelectItemWidget::bindData(const QString _titleStr, const wetalkselectEventItem _data)
{
    m_dataSelectItemInfo = _data;

    ui->labelTitle->setText( _titleStr );
    ui->labelText->setText( _data.text );
    qDebug()<<"SelectItemWidget bindData text:"<<_data.text;
}

void SelectItemWidget::mousePressEvent(QMouseEvent *event)
{
    if( m_dataItemInfo.isCorrect )
    {
        this->setStyleSheet("background-color: #17B6FE;\
                            color: #ffffff;");
    }
    else
    {
        this->setStyleSheet("background-color: #FA2323;\
                            color: #ffffff;");
    }

    emit signal_selectFinish();
}

SelectItemWidget::~SelectItemWidget()
{
    delete ui;
}
