#include "vlcmediamanager.h"
#include "utility/stringutility.h"
#include <QDebug>

VlcMediaManager::VlcMediaManager(QObject *parent) :
    QObject(parent),
    m_mediaPlayer(NULL),
    m_mediaExpression(NULL),
    m_mediaInstance(NULL),
    m_playOverFlag(false),
    m_currentVolume(50),
    currentPlayStatus(MUESIC_PLAY_NONE),
    m_bellLogPlayFlag( false )
{
    init();
}

void VlcMediaManager::init()
{
    m_mediaInstance = libvlc_new( 0, NULL );

    m_updatePalyTimer = new QTimer();
    m_updatePalyTimer->setInterval(1000);
    connect(m_updatePalyTimer,SIGNAL(timeout()),this,SLOT(updatePalyTime()));
}

VlcMediaManager::~VlcMediaManager()
{
    mediaPlayStop();

    if( m_mediaInstance )
        libvlc_release( m_mediaInstance );
}

void VlcMediaManager::updatePalyTime()
{
    if( m_mediaPlayer == NULL )
        return;

    QString curtimestr,durationstr;
    int curtime;
    int duration;

    curtime = libvlc_media_player_get_time(m_mediaPlayer);
    curtimestr = StringUtility::timeTostring( curtime/1000 );

    duration  = libvlc_media_player_get_length(m_mediaPlayer);
    durationstr = StringUtility::timeTostring( duration/1000 );
    if( duration > 0 )
    {
        m_progress = ( curtime*1000.0)/(duration*1.0 );
        m_playTimeText = curtimestr+"/"+durationstr;
    }
    qDebug()<<"updatePalyTime m_playTimeText:"<<m_playTimeText<<m_progress;
    emit updatePlayProgress( m_playTimeText, (int)m_progress );

    //有时候没播完会莫名其妙的停止了,没有专门来调试这部分
    if( libvlc_media_player_get_state( m_mediaPlayer ) == libvlc_Ended || duration < 0
            || ( m_bellLogPlayFlag && curtime/1000 >= m_bellEndTime ) )
    {
//        if( m_progress > 970.0 )
        {
            if( m_bellLogPlayFlag )
                m_bellLogPlayFlag = false;

            emit signal_playOverThenNext(true);

            return;
        }
    }
}

//参数 总时间百分比
void VlcMediaManager::skipPlayPercentage( const int _skipTime )
{
    if( currentPlayStatus == MUESIC_PLAY_NONE )
        return;

    if( m_mediaPlayer == NULL )
        return;

    int _duration  = libvlc_media_player_get_length( m_mediaPlayer );
    skipPlayTime( _skipTime*_duration/1000 );
}

//参数 毫秒数
void VlcMediaManager::skipPlayTime( const int _skipTime )
{
    if( currentPlayStatus == MUESIC_PLAY_NONE )
        return;

    if( m_mediaPlayer == NULL )
        return;

    libvlc_media_player_set_time( m_mediaPlayer, _skipTime );
}

void VlcMediaManager::setPlayStatus(const MUESIC_PLAY_STATUS _playStatus)
{
    currentPlayStatus = _playStatus;
    emit playStateUpdate( _playStatus );
}

MUESIC_PLAY_STATUS VlcMediaManager::getPlayStatus()
{
    return currentPlayStatus;
}

void VlcMediaManager::bellLogPlayStart( const QString &_url, const QString &_startTime,
                                        const QString &_endTime )
{
    m_bellLogPlayFlag = true;

    m_bellStartTime = _startTime.toFloat();
    m_bellEndTime = _endTime.toFloat();

    mediaPlayStart( _url );
}

void VlcMediaManager::mediaPlayStart(const QString &_url)
{
    qDebug()<<"mediaPlayStart url:"<<_url;

    mediaPlayStop();

    m_currentPlayURL = _url;

    QByteArray _urlArray = _url.toLatin1();
    init_mediaPlayer( _urlArray.data() );
    if( !m_mediaPlayer )
    {
        qDebug()<<"mediaPlayStart m_mediaPlayer is null.";
        return;
    }

    /* play the media_player */
    int _mediaRecv = libvlc_media_player_play ( m_mediaPlayer );
    if( _mediaRecv == -1 )
    {
        qDebug()<<"mediaPlayStart libvlc_media_player_play is error.";
        return;
    }

    libvlc_audio_set_volume( m_mediaPlayer, m_currentVolume );
    m_play_flag = true;
    m_playOverFlag = false;
    m_updatePalyTimer->start();
    setPlayStatus( MUESIC_PLAYING_START );

    if( m_bellLogPlayFlag )
        skipPlayTime( m_bellStartTime*1000 );
}

void VlcMediaManager::mediaPlayOrPause()
{

    if( libvlc_media_player_get_state(m_mediaPlayer) == libvlc_Paused )
    {
        libvlc_media_player_set_pause(m_mediaPlayer,0);
//        if( libvlc_media_player_get_state(m_mediaPlayer) == libvlc_Playing )
        {
            m_play_flag = true;
            m_updatePalyTimer->start();
            setPlayStatus( MUESIC_PLAYING_START );
        }
    }
    else if( libvlc_media_player_get_state(m_mediaPlayer) == libvlc_Playing )
    {
        libvlc_media_player_set_pause( m_mediaPlayer, 1 );
//        if( libvlc_media_player_get_state(m_mediaPlayer) == libvlc_Paused )
        {
            m_play_flag = false;
            m_updatePalyTimer->stop();

            setPlayStatus( MUESIC_PLAY_PAUSE );
        }
    }
}

void VlcMediaManager::mediaPlayStop()
{
    if( m_mediaPlayer != NULL )
    {
        libvlc_media_player_stop ( m_mediaPlayer );
        libvlc_media_player_release ( m_mediaPlayer );
        qDebug()<<"mediaPlayStop m_mediaPlayer is null...";
    }
//    m_pause_play->stop();
    m_mediaPlayer = NULL;
    m_mediaExpression = NULL;
    m_play_flag = false;
    m_updatePalyTimer->stop();
    setPlayStatus( MUESIC_PLAY_STOP );

    qDebug()<<"mediaPlayStop....";
}

void VlcMediaManager::setVolume(const int &_volume)
{
    m_currentVolume = _volume;

    if( m_mediaPlayer )
        libvlc_audio_set_volume( m_mediaPlayer, m_currentVolume );
}

int VlcMediaManager::getVolume()
{
    return m_currentVolume;
}

void VlcMediaManager::init_mediaPlayer(const char *url)
{
    if( !m_mediaInstance )
    {
        qDebug()<<"init_mediaPlayer m_mediaInstance is null...";
        return;
    }

    m_mediaExpression = libvlc_media_new_location( m_mediaInstance, url );

    if( m_mediaExpression == NULL )
    {
        qDebug()<<"init_mediaPlayer m_mediaExpression is null...";
        return;
    }
    //libvlc_m = libvlc_media_new_path (libvlc_inst, url);

    /* Create a media player playing environement */
    m_mediaPlayer = libvlc_media_player_new_from_media ( m_mediaExpression );

    if( m_mediaPlayer == NULL )
    {
        qDebug()<<" init_mediaPlayer m_mediaPlayer is null...";
    }

    /* No need to keep the media now */
    libvlc_media_release ( m_mediaExpression );
    m_mediaExpression = NULL;
    //on windows
    //libvlc_media_player_set_hwnd (m_mediaPlayer,(HWND)m_lable->winId());
}
