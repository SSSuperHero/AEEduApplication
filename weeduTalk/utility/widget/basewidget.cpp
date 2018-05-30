#include "basewidget.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QSize>
#include <QApplication>
#include <QLayout>

BaseWidget::BaseWidget(QWidget *parent) : QFrame(parent)
{
    m_rect = getScreenRect();
}

QRect BaseWidget::getScreenRect()
{
    QDesktopWidget * deskTop = QApplication::desktop();
    int curNum = deskTop->screenNumber(this);
    QRect rect = deskTop->screenGeometry( curNum );
//    QRect rect = deskTop->screenGeometry();

    return rect;
}

double BaseWidget::getZoomFactorNum()
{
    int screen_h;
    screen_h = m_rect.height();

    double _zoomFactorNum = 0;
    if( screen_h > DEFINE_SCREEN_HEIGHT )
    {
       _zoomFactorNum = screen_h/DEFINE_SCREEN_HEIGHT;
    }

    return _zoomFactorNum;
}

int BaseWidget::getWidth( const int &_width )
{
    int recWidth = 0;

    int screen_h;
    screen_h = m_rect.height();
    int screen_w;
    screen_w = m_rect.width();
//    if( screen_w == DEFINE_SCREEN_WIDTH )
    if( screen_h <= DEFINE_SCREEN_HEIGHT )
    {
       recWidth = _width;
    }
    else
    {
//        recWidth = ( screen_w*_width )/DEFINE_SCREEN_WIDTH + 0.5;
        recWidth = ( screen_h*_width )*1.1 / DEFINE_SCREEN_HEIGHT + 0.5;
    }

    return recWidth;
}

int BaseWidget::getHeight( const int &_height )
{
    int recHeight = 0;

    int screen_h;

    screen_h = m_rect.height();
    if( screen_h <= DEFINE_SCREEN_HEIGHT )
    {
        recHeight = _height;
    }
    else
    {
        recHeight = ( screen_h*_height )*1.1 / DEFINE_SCREEN_HEIGHT;
    }

    return recHeight;
}

QSize BaseWidget::getSize( const int &_width, const int &_height )
{
    return QSize( getWidth(_width), getHeight(_height) );
}

void BaseWidget::slot_widgetResize()
{
    this->resize( this->width() + 1, this->height() + 1 );
    this->resize( this->width() - 1, this->height() - 1 );
}

void BaseWidget::reSetSize( QWidget *_widget, bool _isSetMax )
{
    if( !_widget )
        return;

    QSize _ret = getSize( _widget->width(), _widget->height() );

    _widget->resize( _ret.width(), _ret.height() );
    _widget->setMinimumSize( _ret );

    if(_isSetMax)
        _widget->setMaximumSize( _ret );

#ifdef Q_OS_MAC

   reSetFont( _widget );

#endif

//    qDebug()<<"reSetSize _ret:" << _ret.width() <<_ret.height();
}

void BaseWidget::reSetCloseIcon( QWidget *_widget )
{
#ifdef Q_OS_MAC

    QSize _ret = getSize( 12, 12 );

    _widget->resize( _ret.width(), _ret.height() );
    _widget->setMinimumSize( _ret );
    _widget->setMaximumSize( _ret );

   QString _styleStr = QString("QPushButton \
   { \
   border-image: url(:/images/%1.png);\
   background-repeat:no-repeat;\
   border:none;\
   }\
   QPushButton:hover\
   {\
   border-image:url(:/images/%2.png);\
   }\
   QPushButton:pressed\
   {\
   border-image:url(:/images/%3.png);\
   }").arg("mac_close").arg("mac_close_hover").arg("mac_close_hover");

   _widget->setStyleSheet( _styleStr );

#endif
}

void BaseWidget::reSetFont( QWidget *_widget )
{
    if( !_widget )
        return;

#ifdef Q_OS_MAC

    QFont _font = _widget->font();
    _font.setPointSize( _font.pointSize() + 2 );
    _widget->setFont( _font );

#endif
}

void BaseWidget::reSetFont(QFont _font, QWidget *_widget )
{
    if( !_widget )
        return;

#ifdef Q_OS_MAC

   _font.setPointSize( _font.pointSize() + 2 );

#endif

    _widget->setFont( _font );
}

void BaseWidget::widgetShowCenter()
{
    move( (m_rect.width() - width())/2,
          (m_rect.height() - height())/2);
}

void BaseWidget::clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0)) != 0)
    {
        //删除widget
        if(item->widget())
        {
            delete item->widget();
            //item->widget()->deleteLater();
        }
        //删除子布局
        QLayout *childLayout = item->layout();
        if(childLayout)
        {
            clearLayout(childLayout);
        }
        delete item;
    }
}


void BaseWidget::enterEvent(QEvent *event)
{
    emit signal_enterWidget();
}

void BaseWidget::leaveEvent(QEvent *event)
{
    emit signal_leaveWidget();
}

