#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QFrame>
#include "config/define.h"

class BaseWidget : public QFrame
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = 0);

    void reSetSize(QWidget *_widget , bool _isSetMax = true);
    int getWidth(const int &_width);
    int getHeight(const int &_height);
    QSize getSize(const int &_width, const int &_height);
    QRect getScreenRect();

    void widgetShowCenter();
    void reSetFont(QWidget *_widget);
    void reSetFont(QFont _font, QWidget *_widget);
    void reSetCloseIcon(QWidget *_widget);
    double getZoomFactorNum();
    void clearLayout(QLayout *layout);
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

signals:
    void signal_enterWidget();
    void signal_leaveWidget();

public slots:
    void slot_widgetResize();
private:

    QRect       m_rect;

};

#endif // BASEWIDGET_H
