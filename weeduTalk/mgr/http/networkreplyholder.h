#ifndef NETWORKREPLYHOLDER_H
#define NETWORKREPLYHOLDER_H

#include <QEvent>
#include <QNetworkReply>
#include <QByteArray>

#define REPLY_SAFE_RELEASE(reply) \
    if (reply)\
    {\
        (reply)->abort();\
        (reply) = NULL;\
    }

class NetWorkReplyHolder: public QObject
{
    Q_OBJECT
public:
    NetWorkReplyHolder(QNetworkReply* reply_, const QString& url, int timeoutMilliseconds);
    ~NetWorkReplyHolder();

    void abort();
    bool getShouldAbort() const;
    void setShouldAbort(bool value);

    void emitOnStartSignal();

    QString getUrl() const;
    void setUrl(const QString &value);

    void savePhpSessionId();
    
signals:
    void signal_onStart();
    void signal_onFinish();
    void signal_onAbort();
    void signal_onSuccess(const QString& response);
    void signal_onFailure(int errorCode);
    void signal_downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void signal_onError(const QString& response);

private slots:
    void slot_readyRead();
    void slot_finished();
    void slot_error(QNetworkReply::NetworkError code);
    void slot_downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void slot_reply_timeout();

    // QObject interface
    void slot_sslErrors(const QList<QSslError> &errors);
protected:
    void customEvent(QEvent *event);

private:
    QNetworkReply* reply;
    QString        url;
    QByteArray     response;
    bool           isError;
    bool           shouldAbort;
    bool           onStartEmitted;
};

#endif // NETWORKREPLYHOLDER_H
