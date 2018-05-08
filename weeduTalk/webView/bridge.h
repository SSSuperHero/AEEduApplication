#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>
#include <QJSValue>
#include <functional>
#include <QVariant>
#include "widget/widgetmanager.h"

class Bridge : public QObject
{
Q_OBJECT
public:
    static Bridge* instance();

    void init();
signals:
    void sigYourName(const QString &name);
    void sendMessageToWeb( const QString strJson );

public slots:
    void sendMessage(QString msg);
    void parseJson(const QByteArray &data);
    void slot_sendMessageToWeb(const MUESIC_PLAY_STATUS _playType, const int _id );

private:
    Bridge();

};

#endif // BRIDGE_H
