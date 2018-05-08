#ifndef ENTITYNETWORKREPLYHOLDER_H
#define ENTITYNETWORKREPLYHOLDER_H
#include "baseentity.h"
#include "networkreplyholder.h"
#include <QSharedDataPointer>

#define REPLY_AUTO_RELEASE(reply_statement) \
{\
    EntityNetworkReplyHolder* reply = (reply_statement);\
    if (reply)\
    {\
        reply->setAutoDeleted(true);\
    }\
}

class EntityNetworkReplyHolder: public QObject
{
    Q_OBJECT
public:
    EntityNetworkReplyHolder(QObject *parent, NetWorkReplyHolder* replyHolder);
    ~EntityNetworkReplyHolder();

    void abort();

    void setAutoDeleted(bool value);

signals:
    void signal_onStart();
    void signal_onFinish();
    void signal_onRawSuccess(const QString& response); //http response ok
    void signal_onSuccess(const QString& response); // ErrorCode is 200, protocol level response ok
    void signal_onFailure(const BaseEntity& baseEntity);
    void signal_onAbort();
    void signal_onError(const QString& response);

private slots:
    void slot_onStart();
    void slot_onFinish();
    void slot_onSuccess(const QString& response);
    void slot_onFailure(int errorCode);
    void slot_onAbort();
    void slot_onError(const QString& response);

private:
    bool isSuccessful(const BaseEntity& baseEntity);
private:
    NetWorkReplyHolder* reply;
    bool autoDeleted;

};

#endif // ENTITYNETWORKREPLYHOLDER_H
