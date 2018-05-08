#ifndef ECHOSLIDER_H
#define ECHOSLIDER_H
#include <QSlider>

class EchoSlider : public QSlider
{
    Q_OBJECT

public:
    EchoSlider(QWidget *parent = 0);

    void setSliderType( const bool &_isHorizontal );

protected:
    void mousePressEvent( QMouseEvent *ev );
    void mouseReleaseEvent(QMouseEvent *ev);

public:
signals:
    void signal_echoSliderClicked( int );

private:
    bool    isHorizontal;
};

#endif // ECHOSLIDER_H
