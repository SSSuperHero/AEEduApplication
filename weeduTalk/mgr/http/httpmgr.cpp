#include "httpmgr.h"
#include "utility/tostringutil.h"

#include <QFileInfo>
#include <QHttpMultiPart>
#include <QNetworkCookie>
#include <QUrlQuery>
#include "utility/userinfo.h"
#include "utility/stringutility.h"
//#include "echoinfo.h"

HttpMgr::HttpMgr():
m_networkAccessMgr( NULL )
{
    m_networkCookieJar = NULL;
    resetNetworkAccessManager();
}

//解决mac端断线重连 无法连接网络的问题
void HttpMgr::resetNetworkAccessManager()
{
//    if( m_networkAccessMgr )
//    {
//        delete m_networkAccessMgr;
//        m_networkAccessMgr = NULL;
//    }

    m_networkAccessMgr = new QNetworkAccessManager(this);
}

void HttpMgr::init()
{
    initFileContentTypeMap();
}

QString HttpMgr::getUrlFailureActionName(const QString &url)
{
    return getUrlActionName(url) + "_failure";
}

QString HttpMgr::getUrlActionName(const QString &url)
{
    QStringList parts = url.split("/");
    if (parts.length() < 2)
    {
        return url;
    }

    return QString("%1_%2").arg(parts[parts.length() - 2])
            .arg(parts[parts.length() - 1]);
}

void HttpMgr::initFileContentTypeMap()
{
    //check https://en.wikipedia.org/wiki/Media_type
    //only handle common types here, for others, add new types below
    contentTypeMap["jpg"] = "image/jpeg";
    contentTypeMap["jpeg"] = "image/jpeg";
    contentTypeMap["png"] = "image/png";
    contentTypeMap["gif"] = "image/gif";
    contentTypeMap["zip"] = "application/zip";
    contentTypeMap["txt"] = "text/plain";
}

void HttpMgr::SavePhpSessionId(const QVariant varCookies)
{
    QList<QNetworkCookie> cookies = varCookies.value< QList<QNetworkCookie> >();
    foreach (const QNetworkCookie& cookie, cookies)
    {
        qInfo("phpsessionid:name:%s, value:%s", qUtf8Printable(cookie.name()), qUtf8Printable(cookie.value()));
        if (cookie.name().toUpper() == "PHPSESSID")
        {
            QString phpSessionId = cookie.value();
            setPhpSessionId(phpSessionId);
        }
    }
}

void HttpMgr::setSslSocket( QNetworkRequest &_request )
{
    QSslConfiguration sslConf;
    sslConf.setPeerVerifyMode( QSslSocket::VerifyNone );
    sslConf.setProtocol(QSsl::TlsV1_0);
    _request.setSslConfiguration( sslConf );
}

void HttpMgr::setNetworkRequest( QNetworkRequest &_request )
{
    char sn[2048] = {0};
    memset(sn,0,2048);

#ifdef Q_OS_MAC
//    setSslSocket( _request );
    _request.setRawHeader("x-c","5");
#else
    _request.setRawHeader("x-c","4");
#endif
    _request.setRawHeader("x-v","1");
    _request.setRawHeader("x-vs","1.0");

    QString _macId = StringUtility::getHostMacAddress();
    QByteArray bytesn((char*)"b679c23816cb5e4c589135ef1d1d35ef");
    _request.setRawHeader("x-sn",bytesn);
    _request.setRawHeader("x-uuid",_macId.toLatin1());

    QString echostr = "echo windows 2.0 20160229;(windows);IDFA ";
    QString id = QString(QLatin1String(_macId.toLatin1().data()));
    QByteArray array;
    array.append(echostr+id);
    _request.setRawHeader("User-Agent",array);
    if(!userInfoMgr::instance()->getToken().isEmpty()){
        _request.setRawHeader("x-ssotoken",array);
    }
}

void HttpMgr::echoClearCookie()
{
//    if( m_networkCookieJar )
//        m_networkCookieJar->deleteCookie();

    m_networkCookieJar = NULL;
}

//这里全是post,需要优化,虽然结果没问题
NetWorkReplyHolder *HttpMgr::post(const QString &urlString, const QString &params,
                                  bool setCookie, int timeoutMilliseconds)
{
    qInfo()<< "post url: , params:" << urlString << params;

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    setNetworkRequest( request );

    if( setCookie && m_networkCookieJar )
        m_networkAccessMgr->setCookieJar( m_networkCookieJar );

    QNetworkReply *reply = m_networkAccessMgr->post(request, params.toUtf8());
    if (!reply)
    {
        qCritical("reply is null");
        return NULL;
    }

    //此消息未被触发
    if (reply->error() == QNetworkReply::UnknownNetworkError)
    {
        resetNetworkAccessManager();
        if( setCookie && m_networkCookieJar )
            m_networkAccessMgr->setCookieJar( m_networkCookieJar );

        reply = m_networkAccessMgr->post(request, params.toUtf8());
        qDebug() << "网络错误:" <<reply->error();
    }


    if( !m_networkCookieJar )
        m_networkCookieJar = m_networkAccessMgr->cookieJar();

    return new NetWorkReplyHolder(reply, urlString, timeoutMilliseconds);
}

NetWorkReplyHolder *HttpMgr::get(const QString &urlString, const HttpParamMap_t &params,
                                 bool setCookie, int timeoutMilliseconds)
{
    qInfo("get url:%s, params:", qUtf8Printable(urlString), qUtf8Printable(ToStringUtil::mapToString(params)));

    QUrl url(urlString);

    if ( !params.isEmpty() )
    {
        //urlencode
        QUrlQuery query;
        QMap<QString, QString>::const_iterator b = params.begin();
        QMap<QString, QString>::const_iterator e = params.end();
        for (; b != e; ++b)
        {
            query.addQueryItem(b.key(), b.value());
        }

        url.setQuery(query);
    }


    QNetworkRequest request(url);

    setNetworkRequest( request );

    if( setCookie && m_networkCookieJar )
        m_networkAccessMgr->setCookieJar( m_networkCookieJar );

    QNetworkReply *reply = m_networkAccessMgr->get(request);
    if (!reply)
    {
        qCritical("reply is null");
        return NULL;
    }

    //此消息未被触发
    if (reply->error() == QNetworkReply::UnknownNetworkError)
    {
        resetNetworkAccessManager();
        if( setCookie && m_networkCookieJar )
            m_networkAccessMgr->setCookieJar( m_networkCookieJar );

        reply = m_networkAccessMgr->get(request);
        qDebug() << "网络错误:" <<reply->error();
    }

    return new NetWorkReplyHolder(reply, urlString, timeoutMilliseconds);
}

NetWorkDownloadReplyHolder *HttpMgr::download(QObject* owner, const QString &urlString,
                                              const QString &dirPath, bool _isResetName)
{
    qInfo("download urlString:%s, path:%s", qUtf8Printable(urlString), qUtf8Printable(dirPath));

    if ( _isResetName && NetWorkDownloadReplyHolder::isFileAlreadyDownloaded(urlString, dirPath))
    {
       qInfo("isFileAlreadyDownloaded true");
       return new NetWorkDownloadReplyHolder(owner, urlString, dirPath, _isResetName, NULL);
    }

    //urlencode?
    QUrl url(urlString);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_networkAccessMgr->get(request);

    if (!reply)
    {
        qCritical("reply is null");
        return NULL;
    }

    return new NetWorkDownloadReplyHolder(owner, urlString, dirPath, _isResetName, reply);
}

NetWorkReplyHolder *HttpMgr::upload(const QString &urlString, const QString &fileControlName,
                                    const QString &filePath, const HttpParamMap_t &params)
{

    qInfo("upload url:%s, fileControlName:%s, filePath:%s", qUtf8Printable(urlString),
          qUtf8Printable(fileControlName), qUtf8Printable(filePath));

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    //handle file
    QHttpPart filePart;

    QString fileContentType = guessFileContentType(filePath);
//    qInfo("fileContentType:%s", qUtf8Printable(fileContentType));

    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(fileContentType));

    QFileInfo fileInfo(filePath);
    QString contentDispositionName = QString("form-data;name=\"%1\";filename=\"%2\"").arg(fileControlName).arg(fileInfo.fileName());
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(contentDispositionName));


    QFile *file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly))
    {
        //release multipart && file
        qCritical("open file failed");
        //return NULL;
    }

    filePart.setBodyDevice(file);
    file->setParent(multiPart);

    multiPart->append(filePart);

    //handle params
    QMap<QString, QString>::const_iterator b = params.begin();
    QMap<QString, QString>::const_iterator e = params.end();
    for (; b != e; ++b)
    {
        const QString& name = b.key();
        const QString& value = b.value();

        QHttpPart textPart;
        QString contentDispositionName = QString("form-data; name=\"%1\"").arg(name);

        textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(contentDispositionName));
        //urlencode?
        textPart.setBody(value.toLocal8Bit());

        multiPart->append(textPart);
    }


    QUrl url(urlString);
    QNetworkRequest request(url);

    QNetworkReply *reply = m_networkAccessMgr->post(request, multiPart);
    if (!reply)
    {
        qCritical("reply is null");
        return NULL;
    }

    return new NetWorkReplyHolder(reply, urlString, -1);
}

QString HttpMgr::guessFileContentType(const QString &filePath)
{
    qInfo("guessFileContentType filePath:%s", qUtf8Printable(filePath));

    QString contentType = "application/octet-stream";

    QFileInfo fileInfo(filePath);
    QString suffix = fileInfo.suffix().trimmed();
    if (suffix.isEmpty())
    {
        qCritical("no suffix");
        return contentType;
    }

    FileContentTypeMap_t::const_iterator p = contentTypeMap.find(suffix.toLower());
    if (p == contentTypeMap.end())
    {
        qCritical("can't find content type with suffix:%s", qUtf8Printable(suffix));
        return contentType;
    }


    return p.value();
}

QString HttpMgr::getPhpSessionId() const
{
    return phpSessionId;
}

void HttpMgr::setPhpSessionId(const QString &value)
{
    qInfo("phpsessionid:setPhpSessionId:%s", qUtf8Printable(value));

    phpSessionId = value;
}



