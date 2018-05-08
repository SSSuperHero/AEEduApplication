#include "networkreplytimeout.h"

NetworkReplyTimeout::NetworkReplyTimeout(QNetworkReply *reply, const int msec) : QObject(reply)
{
    qInfo("timeout:init msec:%d", msec);
    if (reply && reply->isRunning()) {  // 启动单次定时器

        qInfo("timeout:start timer");
        QTimer::singleShot(msec, this, SLOT(onTimeout()));
    }
}

void NetworkReplyTimeout::onTimeout() {  // 处理超时
    qInfo("timeout:onTimeout");
    QNetworkReply *reply = static_cast<QNetworkReply*>(parent());
    if (reply->isRunning()) {
         qInfo("timeout:reply is running, really timeout");

//        reply->deleteLater();
        emit timeout();
    }
}
