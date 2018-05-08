#include "echowebhttpapi.h"
#include "config/echoconfig.h"
#include <QFileInfo>
#include <mgr/http/entitynetworkreplyholder.h>
#include <mgr/http/httpmgr.h>
#include "config/define.h"
#include "utility/userinfo.h"

//EchoWebHttpApi::EchoWebHttpApi(QObject *parent) : QObject(parent)
//{

//}

void EchoWebHttpApi::init()
{

}

QString EchoWebHttpApi::getUrl( const QString &_url )
{
//    return QString(API_TEST_ADDRESS_HEADER) + _url;

    return QString(API_ADDRESS_HEADER) + _url;
}

EntityNetworkReplyHolder *EchoWebHttpApi::login(QObject* replyOwner, const QString &name,
                                                const QString &password)
{
    HttpParamMap_t paramMap;
    paramMap["username"] = name;
    paramMap["password"] = password;
    paramMap["version"] = ECHO_APP_VERSION;

    QString postUrl = getUrl( QString(WEB_ADDRESS_LOGGING) );

    QString param = "username=" + name+"&"+"password=" + password;

    return new EntityNetworkReplyHolder(replyOwner,
                                        HttpMgr::instance()->post(postUrl, param, false, 10000));
}

EntityNetworkReplyHolder *EchoWebHttpApi::getWetalkCourseInfoList( QObject* replyOwner )
{
    QString postUrl = getUrl( QString("components/courses/wetalkgetCourseInfoList/") );
    HttpParamMap_t params;
    params.insert( "access_token", userInfoMgr::instance()->getToken() );

    return new EntityNetworkReplyHolder(replyOwner,
                                        HttpMgr::instance()->get(postUrl, params, true, 5000));
}

EntityNetworkReplyHolder *EchoWebHttpApi::getWetalkgetLevelList( QObject* replyOwner, const int _course_id )
{
    QString postUrl = getUrl( QString("components/courses/wetalkgetLevelList/%1/").arg(QString::number(_course_id)) );
    HttpParamMap_t params;
    params.insert( "access_token", userInfoMgr::instance()->getToken() );

//    postUrl += QString("?access_token=%1").arg( userInfoMgr::instance()->getToken() );

    return new EntityNetworkReplyHolder(replyOwner,
                                        HttpMgr::instance()->get(postUrl, params, true, 5000));
}

EntityNetworkReplyHolder *EchoWebHttpApi::getWetalkUnitList(QObject* replyOwner , const int _course_id, const int _level_id)
{
    QString postUrl = getUrl( QString("components/units/wetalkgetUnitList/%1/%2/")
                              .arg(QString::number(_course_id)).arg(QString::number(_level_id)) );
    HttpParamMap_t params;
    params.insert( "access_token", userInfoMgr::instance()->getToken() );

    return new EntityNetworkReplyHolder(replyOwner,
                                        HttpMgr::instance()->get(postUrl, params, true, 5000));
}

EntityNetworkReplyHolder *EchoWebHttpApi::getWetalkUnitItem( QObject* replyOwner, const int unit_id )
{
    QString postUrl = getUrl( QString("components/lessons/wetalkgetLessonList/%1/").arg(QString::number(unit_id)));
    HttpParamMap_t params;
    params.insert( "access_token", userInfoMgr::instance()->getToken() );

    return new EntityNetworkReplyHolder(replyOwner,
                                        HttpMgr::instance()->get(postUrl, params, true, 5000));
}

EntityNetworkReplyHolder *EchoWebHttpApi::getWetalkPartList( QObject* replyOwner, const int lesson_id )
{
    QString postUrl = getUrl( QString("components/lessonparts/wetalkgetLessonpartList/%1/").arg(QString::number(lesson_id)));
    HttpParamMap_t params;
    params.insert( "access_token", userInfoMgr::instance()->getToken() );

    return new EntityNetworkReplyHolder(replyOwner,
                                        HttpMgr::instance()->get(postUrl, params, true, 5000));
}

EntityNetworkReplyHolder *EchoWebHttpApi::postIsLike( QObject* replyOwner, const QString &_soundId,
                                                const int &_type )
{
    QString postUrl = getUrl( QString(WEB_ADDRESS_SOUND_LIKE_OR_UNLIKE) );

    QString param = "sound_id=" + _soundId + "&type=" + QString::number(_type);

    return new EntityNetworkReplyHolder(replyOwner,
                                        HttpMgr::instance()->post(postUrl, param, true, 5000));
}

