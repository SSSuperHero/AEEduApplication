#include "echowebwidget.h"
#include <QWebEngineProfile>
#include <QWebEnginePage>
#include <QWebChannel>
#include <QWebEngineSettings>
#include <QWebEngineCookieStore>
#include "utility/userinfo.h"
#include "utility/stringutility.h"
#include "bridge.h"


EchoWebWidget::EchoWebWidget(QWidget *parent):
    QWebEngineView(parent)
{
//    this->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, false);
    QWebEngineProfile *_profile = new QWebEngineProfile(this);
//    _profile->setHttpUserAgent( "echo windows 2.0 20160229;(windows);IDFA 48-e2-44-c6-8a-80PFKSUJ2MY9XNC0" );

    m_webInterceptor = new MyQWebEngineUrlRequestInterceptor();
    _profile->setRequestInterceptor(m_webInterceptor);

    QWebEnginePage *page = new QWebEnginePage( _profile, this );

    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject("bridge", (QObject*)Bridge::instance());
    page->setWebChannel(channel);
    page->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    page->profile()->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);

    this->setPage( page );
//    loadUrl();

    m_webEngineHistory = history();
    connect( this, &EchoWebWidget::loadFinished, this, &EchoWebWidget::signal_loadFinish );
}

void EchoWebWidget::setCurrentZoomFactor( double _zoomFactorNum )
{
    qDebug()<<"setCurrentZoomFactor _zoomFactorNum:"<<_zoomFactorNum;

#ifndef Q_OS_MAC

    this->page()->setZoomFactor( 1 + _zoomFactorNum*0.25 );

#endif

}

QString EchoWebWidget::getBaseUrl( const QString &_url )
{
    QString baseUrlStr;

//    baseUrlStr =  QString(WEB_ADDRESS_HEADER) + _url;
    baseUrlStr =  QString(WEB_TEST_ADDRESS_HEADER) + _url;

    return baseUrlStr;
}

void EchoWebWidget::load_url( const QString _url, bool _reLoadFlag)
{
    if( _url.isEmpty() )
        return;

    QString _loadUrl = getBaseUrl( _url );

    m_url = _loadUrl;
    m_reloadFlag = _reLoadFlag;

    m_webInterceptor->setReloadFlag( _reLoadFlag );
    this->load( _loadUrl );

    qDebug()<<"_loadUrl："<<_loadUrl;
}

void EchoWebWidget::testUrl( const QString _url )
{
    this->load( _url );

    qDebug()<<"testUrl _url:"<<_url;
}

void EchoWebWidget::gotoBack()
{
    if( m_webEngineHistory->canGoBack() && m_webEngineHistory->currentItemIndex() > 1)
        m_webEngineHistory->back();
//        this->back();

    qDebug()<<"_currentItemIndex："<<m_webEngineHistory->currentItemIndex();
}

void EchoWebWidget::gotoForward()
{
    if( m_webEngineHistory->canGoForward() )
        m_webEngineHistory->forward();
//    this->forward();

    qDebug()<<"_currentItemIndex："<<m_webEngineHistory->currentItemIndex();
}

void EchoWebWidget::slot_clearCefCookie()
{
//    this->page()->profile()->clearHttpCache(); // 清理缓存
    this->page()->profile()->clearAllVisitedLinks(); // 清理浏览记录
    QWebEngineCookieStore* pCookie = this->page()->profile()->cookieStore();
    pCookie->deleteAllCookies(); // 清理cookie
    pCookie->deleteSessionCookies(); // 清理会话cookie

    m_webEngineHistory->clear();
}

void EchoWebWidget::updateWebPage( const WEB_PAGE_TYPE &_webPage , bool _flag )
{
    QString _url("");

    switch (_webPage)
    {
    case TUI_JIAN_PAGE:
        _url = QString(WEB_ADDRESS_TUI_JIAN);
        break;

    case PING_DAO_PAGE:
        _url = QString(WEB_ADDRESS_PIN_DAO);
        break;

    case SHI_PIN_PAGE:
        _url = QString(WEB_ADDRESS_SHI_PIN);
        break;

    case LING_SHENG_PAGE:
        _url = QString(WEB_ADDRESS_BELL);
        break;

    case FA_BU_PAGE:
        _url = QString(WEB_ADDRESS_FA_BU);
        break;

    case HUI_YUAN_PAGE:
        _url = QString(WEB_ADDRESS_HUI_YUAN);
        break;

    case GOLD_PAGE:
        _url = QString(WEB_ADDRESS_GOLD);
        break;

    case EDIT_USER_INFO_PAGE:
        _url = QString(WEB_ADDRESS_EDIT_USER_INFO);
        break;

    case BELL_MANAGE:
        _url = QString(WEB_ADDRESS_BELL_BUYED);
        break;

    case BELL_MY_MAKE:
        _url = QString(WEB_ADDRESS_BELL_MY_MAKE);
        break;

    default:
        break;
    }

    load_url( _url, _flag );
    qInfo()<<"EchoWebWidget updateWebPage _webPage:"<<_webPage;
}

void EchoWebWidget::loadSoundInfoPage( const QString &_soundId )
{
    QString _url = QString(WEB_ADDRESS_SOUND_INFO_ALL);
    _url += _soundId;

    load_url( _url );
}
void EchoWebWidget::loadMvInfoPage( const QString & _mvId )
{
    QString _url(WEB_ADDRESS_MV_INFO);
    _url += _mvId;

    load_url( _url );
}

void EchoWebWidget::loadeSearchPage( const QString &_searchStr )
{
    QString _url(WEB_ADDRESS_SEARCH_RES);
    _url += _searchStr;

    load_url( _url );
}
