#include "baseentity.h"
#include "entitynetworkreplyholder.h"
#include "httpmgr.h"
#include "utility/jsonutil.h"


EntityNetworkReplyHolder::EntityNetworkReplyHolder(QObject *parent, NetWorkReplyHolder *replyHolder)
    : QObject(parent)
    , reply(replyHolder)
    , autoDeleted(false)
{
    if (reply)
    {
        connect(reply, &NetWorkReplyHolder::signal_onStart, this, &EntityNetworkReplyHolder::slot_onStart);
        connect(reply, &NetWorkReplyHolder::signal_onFinish, this, &EntityNetworkReplyHolder::slot_onFinish);
        connect(reply, &NetWorkReplyHolder::signal_onSuccess, this, &EntityNetworkReplyHolder::slot_onSuccess);
        connect(reply, &NetWorkReplyHolder::signal_onFailure, this, &EntityNetworkReplyHolder::slot_onFailure);
        connect(reply, &NetWorkReplyHolder::signal_onAbort, this, &EntityNetworkReplyHolder::slot_onAbort);
        connect(reply, &NetWorkReplyHolder::signal_onError, this, &EntityNetworkReplyHolder::slot_onError);
    }
}

EntityNetworkReplyHolder::~EntityNetworkReplyHolder()
{
    qInfo("network reply:EntityNetworkReplyHolder dies");


    if (reply)
    {
        qInfo("network reply:NetWorkReplyHolder dies in entity");

        delete reply;
    }
}

void EntityNetworkReplyHolder::abort()
{
    if (reply)
    {
        reply->abort();
    }
}

void EntityNetworkReplyHolder::slot_onStart()
{
    emit signal_onStart();
}

void EntityNetworkReplyHolder::slot_onFinish()
{
    emit signal_onFinish();

//    qInfo("network reply:self deleteLater");

    if (autoDeleted)
    {
        qInfo("autodeleted, this:%x", this);
//        this->deleteLater();
    }
}

void EntityNetworkReplyHolder::slot_onSuccess(const QString &response)
{
    emit signal_onRawSuccess(response);

    BaseEntity entity;
    fromJson(response, entity);

    if (!isSuccessful(entity))
    {
        if (reply)
        {
//            actionError(HttpMgr::getUrlFailureActionName(reply->getUrl()), response);
        }
        emit signal_onFailure(entity);
    } else {
        emit signal_onSuccess(response);
    }
}

void EntityNetworkReplyHolder::slot_onFailure(int errorCode)
{
    //set error msg according to error code
    emit signal_onFailure(BaseEntity(errorCode, "failed"));
}

void EntityNetworkReplyHolder::slot_onAbort()
{
    emit signal_onAbort();
}

void EntityNetworkReplyHolder::slot_onError(const QString &response)
{
    emit signal_onError(response);
}

bool EntityNetworkReplyHolder::isSuccessful(const BaseEntity &baseEntity)
{
    return baseEntity.errcode == 0;
}

void EntityNetworkReplyHolder::setAutoDeleted(bool value)
{
    autoDeleted = value;
}
