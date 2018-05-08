#ifndef HTTPMGR_H
#define HTTPMGR_H

#include <utility/singletonmgrbase.h>
#include <qnetworkaccessmanager.h>
#include <QMap>
#include "networkreplyholder.h"
#include "networkdownloadreplyholder.h"
#include "mybasesingleton.h"

typedef QMap<QString, QString> HttpParamMap_t;
class HttpMgr: public SingletonMgrBase
{
    Q_OBJECT

#ifdef Q_OS_MAC
    MY_DECLARE_SINGLETON(HttpMgr)
#else
    DECLARE_SINGLETON(HttpMgr)
    // SingletonMgrBase interface
#endif

public:
    HttpMgr();
    void init();
    static QString getUrlFailureActionName(const QString& url);
    static QString getUrlActionName(const QString& url);

public:
    NetWorkReplyHolder* post(const QString& url, const QString &params,
                             bool setCookie, int timeoutMilliseconds = -1);
    NetWorkReplyHolder* get(const QString& url, const HttpParamMap_t &params, bool setCookie,
                            int timeoutMilliseconds = -1);

public:
    NetWorkDownloadReplyHolder* download(QObject* owner, const QString& url,
                                         const QString& dirPath, bool _isResetName = true );
    NetWorkReplyHolder* upload(const QString& url, const QString& fileControlName,
                               const QString& filePath, const HttpParamMap_t& params);


    void initFileContentTypeMap();

    void SavePhpSessionId(const QVariant varCookies);

    QString getPhpSessionId() const;
    void setPhpSessionId(const QString &value);

    void echoClearCookie();
private:
    QString guessFileContentType(const QString& filePath);
    void setNetworkRequest(QNetworkRequest &_request);
    void setSslSocket(QNetworkRequest &_request);
    void resetNetworkAccessManager();

private:
    QNetworkAccessManager *m_networkAccessMgr;

    typedef QMap<QString, QString> FileContentTypeMap_t;
    FileContentTypeMap_t  contentTypeMap;
    QString               phpSessionId;

    QNetworkCookieJar     *m_networkCookieJar;

};

#endif // HTTPMGR_H
