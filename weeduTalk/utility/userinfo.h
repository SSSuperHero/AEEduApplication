#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>
#include "mgr/http/module/echowebhttpdataentity.h"
#include "utility/singletonmgrbase.h"
#include "mybasesingleton.h"

class UserInfo
{
    loginDetailsInfoEntity m_userDetailsInfo;
    QString m_token;
};

class userInfoMgr : public SingletonMgrBase
{
    Q_OBJECT

#ifdef Q_OS_MAC
    MY_DECLARE_SINGLETON(userInfoMgr)
#else
    DECLARE_SINGLETON(userInfoMgr)
    // SingletonMgrBase interface
#endif

public:
//    explicit userInfoMgr(QObject *parent = 0);

    void init();
    QString getToken();
    void setToken(const QString &_token);

    void setUserInfo( const loginDetailsInfoEntity &_info );
    loginDetailsInfoEntity getUserInfo();
signals:

public slots:

private:
    loginDetailsInfoEntity m_userInfo;
    QString m_token;
};

#endif // USERINFO_H
