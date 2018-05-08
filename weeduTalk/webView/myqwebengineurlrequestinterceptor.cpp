#include "myqwebengineurlrequestinterceptor.h"
#include <QDebug>
#include "utility/stringutility.h"
#include "config/define.h"
#include "utility/userinfo.h"

MyQWebEngineUrlRequestInterceptor::MyQWebEngineUrlRequestInterceptor()
{

}

bool MyQWebEngineUrlRequestInterceptor::get_header(QWebEngineUrlRequestInfo &info)
{
//    if( userInfoMgr::instance()->getToken().isEmpty() )
//        return false;

    qDebug()<<"get_header...";
    char sn[2048] = {0};
    memset(sn,0,2048);

    QString _macId = StringUtility::getHostMacAddress();

    QByteArray bytesn((char*)"b679c23816cb5e4c589135ef1d1d35ef");
    info.setHttpHeader("x-sn",bytesn.data());
    info.setHttpHeader("x-uuid",_macId.toLatin1().data() );
    QString echostr = "echo windows 2.0 20160229;(windows);IDFA ";
    QString id = QString(QLatin1String(_macId.toLatin1().data()));
    QByteArray array;
    array.append(echostr+id);
    info.setHttpHeader("User-Agent", array);
    qInfo()<<"User-Agent:"<<array.data();
    if( !userInfoMgr::instance()->getToken().isEmpty() )
        info.setHttpHeader("x-ssotoken",userInfoMgr::instance()->getToken().toLatin1());

#ifdef Q_OS_MAC
    info.setHttpHeader("x-c", "5");
#else
    info.setHttpHeader("x-c", "4");
#endif

    info.setHttpHeader("x-v", "1");
    info.setHttpHeader("x-vs", "1.0");
    return true;
}

void MyQWebEngineUrlRequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    QString strInfo = "";
    switch (info.resourceType())
    {
    case 0:  //Top level page
        strInfo = "ResourceTypeMainFrame";

//        if( m_reloadFlag )
//        {
            get_header( info );
//            m_reloadFlag = false;
//        }
        break;

    case 1:  //Frame
        strInfo = "ResourceTypeSubFrame";
        break;

    case 2:  //CSS stylesheet
        strInfo = "ResourceTypeStylesheet";
        break;

    case 3:  //External script
        strInfo = "ResourceTypeScript";
        break;

    case 4:  //Image
        strInfo = "ResourceTypeImage";
        break;

    case 5:  //Font
        strInfo = "ResourceTypeFontResource";
        break;

    case 6:  //Sub-resource
        strInfo = "ResourceTypeSubResource";
        break;

    case 7:  //Plugin object
        strInfo = "ResourceTypeObject";
        break;

    case 8:  //Media resource
        strInfo = "ResourceTypeMedia";

        break;

    case 9:  //Resource of dedicated worker
        strInfo = "ResourceTypeWorker";
        break;

    case 10:  //Resource of shared worker
        strInfo = "ResourceTypeSharedWorker";
        break;

    case 11:  //Explicitly requested prefetch
        strInfo = "ResourceTypePrefetch";
        break;

    case 12:  //Favicon
        strInfo = "ResourceTypeFavicon";
        break;

    case 13: //XML http request
        strInfo = "ResourceTypeXhr";

        get_header( info );

        break;

    case 14: //Ping request
        strInfo = "ResourceTypePing";
        break;

    case 15: //Resource of service worker
        strInfo = "ResourceTypeServiceWorker";
        break;

    case 16: //Unknown resource
        strInfo = "ResourceTypeUnknown";
        break;

    default:
        strInfo = "Unknown type";
        break;
    }

//    qDebug() << "RequestMethod===" << info.requestMethod() << "\n"
//        << "RequestUrl===" << info.requestUrl() << "\n";
//    qDebug() << "RequestType===" << strInfo;

    //Set the value of the Accept-Language HTTP request-header.
    info.setHttpHeader("Accept-Language", "zh-CN");
}

void MyQWebEngineUrlRequestInterceptor::setReloadFlag( const bool _flag )
{
    m_reloadFlag = _flag;
}
