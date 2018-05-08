#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#include <QObject>
#include "weeduloginwidget.h"
#include "weedumainwidget.h"

class WidgetManager : public QObject
{
    Q_OBJECT
public:
    explicit WidgetManager(QObject *parent = nullptr);

    void init();

signals:

public slots:
    void slot_loginSuccess();

private:
    WeeduLoginWidget        *m_loginWidget;
    WeeduMainWidget         *m_weeduMainWidget;
};

#endif // WIDGETMANAGER_H
