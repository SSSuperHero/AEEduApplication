#ifndef NETWORKREPLYTIMEOUT_H
#define NETWORKREPLYTIMEOUT_H
#include <QObject>
#include <QTimer>
#include <QNetworkReply>

class NetworkReplyTimeout: public QObject
{
    Q_OBJECT

public:
    NetworkReplyTimeout(QNetworkReply *reply, const int msec);

  signals:
      void timeout();  // 超时信号 - 供进一步处理

  private slots:
      void onTimeout();
  };

#endif // NETWORKREPLYTIMEOUT_H
