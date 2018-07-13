#ifndef ECHOWEBHTTPAPI_H
#define ECHOWEBHTTPAPI_H

#include <QObject>
#include <utility/singletonmgrbase.h>
#include "mybasesingleton.h"
#include <mgr/http/entitynetworkreplyholder.h>
#include "config/define.h"
#include "mgr/http/module/echohttpinfoentity.h"

class EchoWebHttpApi : public SingletonMgrBase
{
    Q_OBJECT

#ifdef Q_OS_MAC
    MY_DECLARE_SINGLETON(EchoWebHttpApi)
#else
    DECLARE_SINGLETON(EchoWebHttpApi)
    // SingletonMgrBase interface
#endif

public:
    void init();
public:
    static EntityNetworkReplyHolder* login(QObject* replyOwner, const QString& name,
                                           const QString& password);

    static EntityNetworkReplyHolder *getWetalkUnitList( QObject *replyOwner, const int _course_id,  const int _level_id  );
    static EntityNetworkReplyHolder *getWetalkUnitItem( QObject* replyOwner, const int unit_id );
    static EntityNetworkReplyHolder *getWetalkPartList( QObject* replyOwner, const int lesson_id );
    static EntityNetworkReplyHolder *getWetalkCourseInfoList(QObject *replyOwner);
    static EntityNetworkReplyHolder *getWetalkgetLevelList( QObject *replyOwner, const int _course_id );
private:
    static QString getUrl(const QString &_url);
};

#endif // ECHOWEBHTTPAPI_H
