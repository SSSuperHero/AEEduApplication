#include "basemainwidget.h"
#include <QPainter>
#include <qmath.h>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>
#include <QtCore/qmath.h>


BaseMainWidget::BaseMainWidget(QWidget *parent)
    : BaseWidget(parent),
    frameless(new FrameLess(this)),
    RoundedFlag(false)
{ 
    qInfo("BaseMainWidget created:0x%x", this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint );
    this->setAutoFillBackground(true);
    //任务栏
    setWindowIcon(QIcon(":/image/logo.png"));
}


BaseMainWidget::~BaseMainWidget()
{
     qInfo("BaseMainWidget destructed:0x%x", this);

    if (frameless)
    {
        delete frameless;
    }
}

void BaseMainWidget::setResizeEnabled(bool value)
{
    if (frameless)
    {
        frameless->setResizeEnabled(value);
    }
}

void BaseMainWidget::setRoundedEnabled( const int &_roundNum, bool flag )
{
    RoundedFlag = flag;
    RoundedNum = _roundNum;

    if( RoundedFlag )
    {
        setAttribute(Qt::WA_TranslucentBackground, true);
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint
                       | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
                       | Qt::WindowMaximizeButtonHint);
    }
}

void BaseMainWidget::paintEvent(QPaintEvent *event)
{
    if( RoundedFlag )
    {
        QPainter p(this);
        p.drawRoundedRect(0, 0, width() - 1, height() - 1, RoundedNum, RoundedNum);
    }

    QWidget::paintEvent(event);
}

void BaseMainWidget::showEvent(QShowEvent *event)
{
    slot_widgetResize();
}

void BaseMainWidget::closeEvent(QCloseEvent *)
{
    qInfo("BaseMainWidget closeEvent:0x%x", this);

    emit signal_close();
}
