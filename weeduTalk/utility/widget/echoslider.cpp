#include "echoslider.h"
#include <QMouseEvent>

EchoSlider::EchoSlider( QWidget *parent ) :
    QSlider( parent ),
    isHorizontal( true )
{

}

void EchoSlider::setSliderType(const bool &_isHorizontal)
{
    isHorizontal = _isHorizontal;
}

void EchoSlider::mousePressEvent( QMouseEvent *ev )
{
    QSlider::mousePressEvent(ev);

//    double pos = 0;
//    if( isHorizontal )
//        pos = ev->pos().x() / (double)width();
//    else
//        pos = ((double)height() - ev->pos().y()) / (double)height();

//    int _value = pos * (maximum() - minimum()) + minimum();
//    setValue( _value );

//    emit signal_echoSliderClicked( _value );
}

void EchoSlider::mouseReleaseEvent(QMouseEvent *ev)
{
    double pos = 0;
    if( isHorizontal )
        pos = ev->pos().x() / (double)width();
    else
        pos = ((double)height() - ev->pos().y()) / (double)height();

    int _value = pos * (maximum() - minimum()) + minimum();
    setValue( _value );

    emit signal_echoSliderClicked( _value );
}
