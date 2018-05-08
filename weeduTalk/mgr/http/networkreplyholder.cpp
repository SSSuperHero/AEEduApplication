#include "httpmgr.h"
#include "networkreplyholder.h"
#include "networkreplytimeout.h"
#include <QTimer>
#include <QApplication>
#include <QNetworkCookie>

static QEvent::Type EVENT_TYPE_ON_START =  static_cast<QEvent::Type>(QEvent::User + 1);
static QEvent::Type EVENT_TYPE_ON_ABORT =  static_cast<QEvent::Type>(QEvent::User + 2);


NetWorkReplyHolder::NetWorkReplyHolder(QNetworkReply* reply_, const QString &url_, int timeoutMilliseconds)
    : reply(reply_)
    , url(url_)
    , isError(false)
    , shouldAbort(false)
    , onStartEmitted(false)
{
    //can event be deleted automatically?
    QApplication::postEvent(this, new QEvent(EVENT_TYPE_ON_START));

//    qDebug("connect reply signals");
    connect(reply, &QIODevice::readyRead, this, &NetWorkReplyHolder::slot_readyRead);
    connect(reply, &QNetworkReply::finished, this, &NetWorkReplyHolder::slot_finished);
    connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &NetWorkReplyHolder::slot_error);
    connect(reply, &QNetworkReply::downloadProgress, this, &NetWorkReplyHolder::slot_downloadProgress);
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),this, SLOT(slot_sslErrors(QList<QSslError>)));

    if (timeoutMilliseconds > 0)
    {
        qInfo("timeout:init timeoutMilliseconds:%d", timeoutMilliseconds);
        NetworkReplyTimeout *replyTimeout = new NetworkReplyTimeout(reply, timeoutMilliseconds);
        connect(replyTimeout, &NetworkReplyTimeout::timeout, this, &NetWorkReplyHolder::slot_reply_timeout);
    }
}


NetWorkReplyHolder::~NetWorkReplyHolder()
{
    qInfo("network reply:NetWorkReplyHolder dies");

     setShouldAbort(true);

    if (reply)
    {
        reply->abort();

        qInfo("network reply:QNetworkReply dies");
        delete reply;
    }
}

void NetWorkReplyHolder::abort()
{
     setShouldAbort(true);

    if (reply)
    {
        reply->abort();
        reply->close();

        //reply should set to NULL
    }

    QApplication::postEvent(this, new QEvent(EVENT_TYPE_ON_ABORT));
}

void NetWorkReplyHolder::emitOnStartSignal()
{
    qInfo("emitOnStartSignal");

    emit signal_onStart();

    onStartEmitted = true;
}

void NetWorkReplyHolder::customEvent(QEvent *event)
{
    if (event && event->type() == EVENT_TYPE_ON_START)
    {
        qInfo("recv EVENT_TYPE_ON_START");

        if (shouldAbort)
        {
            qWarning("abort");
            return;
        }

        emitOnStartSignal();

    }
    else if (event->type() == EVENT_TYPE_ON_ABORT)
    {
        qInfo("recv EVENT_TYPE_ON_ABORT");
        emit signal_onAbort();
    }
}

QString NetWorkReplyHolder::getUrl() const
{
    return url;
}

void NetWorkReplyHolder::setUrl(const QString &value)
{
    url = value;
}

bool NetWorkReplyHolder::getShouldAbort() const
{
    return shouldAbort;
}

void NetWorkReplyHolder::setShouldAbort(bool value)
{
    qInfo("abort:setShouldAbort:%d", value);

    shouldAbort = value;
}
void NetWorkReplyHolder::slot_readyRead()
{
    QByteArray byteArray = reply->readAll();

    response.append(byteArray);
}

void NetWorkReplyHolder::savePhpSessionId()
{
    qInfo("phpsessionid:savePhpSessionId");
    if (!reply)
    {
        qCritical("phpsessionid:empty reply");
        return;
    }

    QVariant varRequestCookies = reply->request().header(QNetworkRequest::CookieHeader);
    qInfo("phpsessionid:save request sessionid");
    HttpMgr::instance()->SavePhpSessionId(varRequestCookies);

    QVariant varResponseCookies = reply->header(QNetworkRequest::SetCookieHeader);
    qInfo("phpsessionid:save response sessionid");
    HttpMgr::instance()->SavePhpSessionId(varResponseCookies);
}

void NetWorkReplyHolder::slot_sslErrors(const QList<QSslError> &errors)
{
    qInfo()<<"slot_sslErrors errors:"<<errors;
}

void NetWorkReplyHolder::slot_finished()
{
    if (isError)
    {
        qInfo("already handled in error");
        return;
    }

    if (shouldAbort)
    {
        qWarning("abort");
        return;
    }

    savePhpSessionId();

    //response might not string
    qInfo("signal_onSuccess, url:%s, response:%s", qUtf8Printable(url), qUtf8Printable(response));
    emit signal_onSuccess(response);

    qInfo("signal_onFinish");
    emit signal_onFinish();
}

void NetWorkReplyHolder::slot_error(QNetworkReply::NetworkError code)
{
    qCritical("NetWorkReplyHolder slot_error, code:%d", code);
    isError = true;

    if (shouldAbort)
    {
        qWarning("abort");
//        actionError(HttpMgr::getUrlFailureActionName(url), "{abort:true}");
        qCritical("NetWorkReplyHolder abort");
        return;
    }

    if (!onStartEmitted)
    {
       //拔网线的时候，slot_error可能先emit,然后才轮到onStart
       emitOnStartSignal();
    }

    qInfo("signal_onFinish");
    emit signal_onFinish();

    qInfo("signal_onFailure");
    //use minus error code to identity low level error(not protocol level error)
    int errorCode = -(int)code;

//    actionError(HttpMgr::getUrlFailureActionName(url),QString("{errorCode:%1}").arg(errorCode));

    emit signal_onFailure(errorCode);

    qInfo()<<"signal_onError:" << response;
    emit signal_onError( response );
}

void NetWorkReplyHolder::slot_downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
//    qDebug("slot_downloadProgress bytesReceived:%lld, bytesTotal:%lld", bytesReceived, bytesTotal);

    //why bytesTotal is -1?
    if (bytesTotal == -1)
    {
        return;
    }

    if (shouldAbort)
    {
        qWarning("abort");
        return;
    }

    emit signal_downloadProgress(bytesReceived, bytesTotal);
}

void NetWorkReplyHolder::slot_reply_timeout()
{
    qCritical("timeout:slot_reply_timeout, abort, emit failure");
    abort();

    emit signal_onFailure(QNetworkReply::TimeoutError);
}


