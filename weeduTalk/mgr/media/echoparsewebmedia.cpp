#include "echoparsewebmedia.h"
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

void ThreasWork::run()
{
    while(m_run)
    {
        m_lock.lock();
        while(!m_queue.isEmpty())
        {
            QueueData  _data = m_queue.dequeue();
            emit sendThreadData( _data.m_name, _data.m_param );
            QThread::msleep(1);
        }
        m_waite.wait(&m_lock);
        m_lock.unlock();
        QThread::msleep(100);
    }
}

void ThreasWork::addQueue(const QString &_name,const QJsonObject &_param)
{
    QueueData _data;
    _data.m_name=_name;
    _data.m_param=_param;
    m_lock.lock();
    m_queue.enqueue( _data );
    m_lock.unlock();

}

void ThreasWork::start_work()
{
    m_waite.wakeOne();
}


EchoParseWebMedia::EchoParseWebMedia(QObject *parent) :
    QObject(parent)
{
    initMap();

    m_threadWork = new ThreasWork();
    connect(m_threadWork, &ThreasWork::sendThreadData,
                     this, &EchoParseWebMedia::ParseWebMsg );
    m_threadWork->start();
}

void EchoParseWebMedia::addWebMediaMsg(const QString &_name,const QJsonObject &_param)
{
    m_threadWork->addQueue( _name, _param );
}
void EchoParseWebMedia::do_cmd()
{
    m_threadWork->start_work();
}

void EchoParseWebMedia::webViewWidgetClose( QJsonObject )
{
//    g_pWidgetManager->showLogWidget();
    emit signal_webWidgetClose();
}

void EchoParseWebMedia::sound_play_do(QJsonObject param)
{
    if(!param.isEmpty())
    {
        int _soundId = param["id"].toInt();

        qDebug()<<"sound_play_do _soundId:" << _soundId;
        emit signal_soundPlayDo( _soundId, true );
    }
}

void EchoParseWebMedia::bell_play_do(QJsonObject param)
{
    if(!param.isEmpty())
    {
        int _soundId = 0;
        if( param["id"].isString() )
        {
            QString _soundIdStr = param["id"].toString();
            _soundId = _soundIdStr.toInt();
        }
        else
            _soundId = param["id"].toInt();

        emit signal_bellPlayDo( _soundId );
    }
}

void EchoParseWebMedia::bell_log_play_do(QJsonObject param)
{
    if(!param.isEmpty())
    {
        int _soundId = 0;
        if( param["id"].isString() )
        {
            QString _soundIdStr = param["id"].toString();
            _soundId = _soundIdStr.toInt();
        }
        else
            _soundId = param["id"].toInt();

        emit signal_bellLogPlayDo( _soundId );
    }
}

void EchoParseWebMedia::status_mv_play(QJsonObject)
{
//    g_pWidgetManager->stop_play_muesic();
    emit signal_videoPlayDo();
}
void EchoParseWebMedia::sound_play_list(QJsonObject param)
{
    if(!param.isEmpty())
    {
        QJsonArray _soundArr = param.value("ids").toArray();
        emit signal_soundPlayListDo( _soundArr );
    }
}
void EchoParseWebMedia::play_next_sound(QJsonObject param)
{
    if(!param.isEmpty())
    {
        QString _soundId = param.value("id").toString();
        emit signal_soundNextPlayDo( _soundId.toInt() );
    }
}
void EchoParseWebMedia::add_sound_to_cur_list(QJsonObject param)
{
    if(!param.isEmpty())
    {
        QString _soundId = param.value("id").toString();
        emit signal_soundAddPlayList( _soundId.toInt() );
    }
}

void EchoParseWebMedia::pause_palue_play(QJsonObject param)
{
    if(!param.isEmpty())
    {
        int _soundId = param.value("id").toInt();
        emit signal_soundPauseDo( _soundId );
    }
}

void EchoParseWebMedia::main_web_mini(QJsonObject)
{
    signal_webMusicInfoMin( false );
}

void EchoParseWebMedia::beel_make_save( QJsonObject param )
{
    if( param.isEmpty() )
        return;

    qDebug()<<"beel_make_save param:" << param;
    echoBellEditInfo _beelInfo;

    _beelInfo.sound_id = param.value("id").toInt();
    _beelInfo.start_time = QString::number( param.value("stime").toDouble() );
    _beelInfo.end_time = QString::number( param.value("etime").toDouble() );
    _beelInfo.sound_source = param.value("source").toString();
    _beelInfo.times = _beelInfo.end_time.toFloat() - _beelInfo.start_time.toFloat();

    if( _beelInfo.times < 1 )
        return;

    if( _beelInfo.sound_id > 0 )
        emit signal_bellMakeSave( _beelInfo );
}

void EchoParseWebMedia::bell_download_log_do(QJsonObject param)
{
    if(!param.isEmpty())
    {
        int _soundId = 0;
        if( param.value("id").isString() )
        {
            QString _soundIdStr = param.value("id").toString();
            _soundId = _soundIdStr.toInt();
        }
        else
            _soundId = param.value("id").toInt();

        emit signal_BellDownloadLogDo( _soundId );
    }
}

void EchoParseWebMedia::bell_download_do(QJsonObject param)
{
    if(!param.isEmpty())
    {
        int _soundId = 0;
        if( param.value("id").isString() )
        {
            QString _soundIdStr = param.value("id").toString();
            _soundId = _soundIdStr.toInt();
        }
        else
            _soundId = param.value("id").toInt();

        emit signal_BellDownloadDo( _soundId );
    }
}

void EchoParseWebMedia::statues_page_change( QJsonObject param )
{
    if( param.isEmpty() )
        return;

    QString _pageStr = param.value("name").toString();
    if( !g_webPageMap.contains(_pageStr) )
        return;

    WEB_PAGE_TYPE _webPage = g_webPageMap[_pageStr];
    if( _webPage == SHI_PIN_INFO_PAGE )
        emit signal_videoPlayDo();

    emit signal_webPageChange( _webPage );
}

void EchoParseWebMedia::user_reg_after(QJsonObject param)
{
    if( !param.isEmpty() )
    {
        QString _username = param.value("username").toString();
        QString _password = param.value("password").toString();

        emit signal_webWidgetClose();
        emit signal_userRegAfter( _username, _password );
    }
}

void EchoParseWebMedia::sys_brower_open(QJsonObject param)
{
    if( !param.isEmpty() )
    {
        QString _pathUrl = param.value("path").toString();

        emit signal_sysBrowerOpen( _pathUrl );
    }
}

void EchoParseWebMedia::openExternalBrowser( QJsonObject param )
{
    if( !param.isEmpty() )
    {
        QString _url = param.value("url").toString();

        QDesktopServices::openUrl(QUrl( _url ));
    }
}

void EchoParseWebMedia::mainWebShowtype( const WIDGET_SHOW_TYPE _showType )
{
    emit signal_changeWidgetShowType( _showType );
}

void EchoParseWebMedia::initMap()
{
    g_webReplyMap.insert(QString("status.page.change"),STATUES_PAGE_CHANGE);
    g_webReplyMap.insert(QString("webview.ui.close"),CMD_HIDE_REGISTER_WIDGET);
    g_webReplyMap.insert(QString("sound.play.do"),CMD_SOUND_PLAY_DO);
    g_webReplyMap.insert(QString("status.mv.play"),CMD_STATUS_MV_PLAY);
    g_webReplyMap.insert(QString("sound.play.lists"),CMD_SOUND_PLAY_LIST);
    g_webReplyMap.insert(QString("sound.play.next"),CMD_PLAY_NEXT_SOUND);
    g_webReplyMap.insert(QString("sound.play.push"),CMD_ADD_SOUND_TO_CUR_LIST);
    g_webReplyMap.insert(QString("sound.play.pause"),CMD_LAUSE_PALUE_PLAY);
    g_webReplyMap.insert(QString("webview.ui.mini"),CMD_MAIN_WEB_MINI);
    g_webReplyMap.insert(QString("webview.ui.init"),CMD_MAIN_WEB_INIT);
    g_webReplyMap.insert(QString("webview.ui.max"),CMD_MAIN_WEB_MAX);
    g_webReplyMap.insert(QString("bell.play.do"),CMD_BELL_PLAY_DO);
    g_webReplyMap.insert(QString("user.reg.after"),CMD_USER_REG_AFTER);
    g_webReplyMap.insert(QString("sys.brower.open"),CMD_SYS_BROWER_OPEN);
    g_webReplyMap.insert(QString("bell.make.save"),CMD_BELL_MAKE_SAVE);
    g_webReplyMap.insert(QString("bell.download.do"),CMD_BELL_DOWNLOAD_DO);
    g_webReplyMap.insert(QString("bell.download.log.do"),CMD_BELL_DOWNLOAD_LOG_DO);
    g_webReplyMap.insert(QString("bell.log.play.do"),CMD_BELL_LOG_PLAY_DO);
    g_webReplyMap.insert(QString("open.external.browser"),CMD_OPEN_EXTERNAL_BROWSER);

    g_webPageMap.insert(QString("SoundInfo"),SOUND_INFO_PAGE);
    g_webPageMap.insert(QString("index"),TUI_JIAN_PAGE);
    g_webPageMap.insert(QString("ChannelIndex"),PING_DAO_PAGE);
    g_webPageMap.insert(QString("MvIndex"),SHI_PIN_PAGE);
    g_webPageMap.insert(QString("MvInfo"),SHI_PIN_INFO_PAGE);
    g_webPageMap.insert(QString("BellIndex"),LING_SHENG_PAGE);
    g_webPageMap.insert(QString("BellCheck"),LING_SHENG_PAGE);
    g_webPageMap.insert(QString("BellMake"),LING_SHENG_PAGE);
    g_webPageMap.insert(QString("BellMine"),LING_SHENG_PAGE);
    g_webPageMap.insert(QString("BellLiked"),LING_SHENG_PAGE);
    g_webPageMap.insert(QString("BellBuyed"),LING_SHENG_PAGE);
    g_webPageMap.insert(QString("BellHot"),LING_SHENG_PAGE);
    g_webPageMap.insert(QString("SoundUpload"),FA_BU_PAGE);
    g_webPageMap.insert(QString("SearchIndex"),SEARCH_INDEX_PAGE);
}

void EchoParseWebMedia::ParseWebMsg( QString _name, QJsonObject _param )
{

    qDebug()<<"ParseWebMsg _name:" << _name;
    if( g_webReplyMap.contains(_name) )
    {
         WEB_CMD_TYPE _cmdType = g_webReplyMap[_name];

         switch (_cmdType)
         {
         case CMD_HIDE_REGISTER_WIDGET:
             webViewWidgetClose( _param );
             break;

         case CMD_SOUND_PLAY_DO:
             sound_play_do( _param );
             break;

         case CMD_BELL_PLAY_DO:
             bell_play_do( _param );
             break;

         case CMD_BELL_LOG_PLAY_DO:
             bell_log_play_do( _param );
             break;

         case CMD_STATUS_MV_PLAY:
             status_mv_play( _param );
             break;

         case CMD_SOUND_PLAY_LIST:
             sound_play_list( _param );
             break;

         case CMD_PLAY_NEXT_SOUND:
             play_next_sound( _param );
             break;

         case CMD_ADD_SOUND_TO_CUR_LIST:
             add_sound_to_cur_list( _param );
             break;

         case CMD_LAUSE_PALUE_PLAY:
             pause_palue_play( _param );
             break;

         case CMD_MAIN_WEB_MINI:
             main_web_mini( _param );
             break;

         case CMD_MAIN_WEB_INIT:
             mainWebShowtype( WIDGET_SHOW_NORMAL );
             break;

         case CMD_MAIN_WEB_MAX:
             mainWebShowtype( WIDGET_SHOW_MAX );
             break;

         case CMD_USER_REG_AFTER:
             user_reg_after( _param );
             break;

         case CMD_SYS_BROWER_OPEN:
             sys_brower_open( _param );
             break;

         case STATUES_PAGE_CHANGE:
             statues_page_change( _param );
             break;

         case CMD_BELL_MAKE_SAVE:
             beel_make_save( _param );
             break;

         case CMD_BELL_DOWNLOAD_DO:
             bell_download_do( _param );
             break;

         case CMD_BELL_DOWNLOAD_LOG_DO:
             bell_download_log_do( _param );
             break;

         case CMD_OPEN_EXTERNAL_BROWSER:
             openExternalBrowser( _param );
             break;

         default:
             break;
         }
    }
}
