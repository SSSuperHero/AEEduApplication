#include "mgr/media/mediaplaymanager.h"

using namespace QtAV;

MediaPlayManager::MediaPlayManager( QObject *parent ):
    QObject(parent),
    m_mediaPlayer(NULL),
    m_currentPlayDuration(0),
    m_playOverFlag(false),
    m_currentVolume(50.0),
    currentPlayStatus(MUESIC_PLAY_NONE)
{
    init();
}

void MediaPlayManager::init()
{
    m_mediaPlayer = new AVPlayer(this);

    QStringList _decoderlist;
//    _decoderlist.append("dxva");
    _decoderlist.append("FFmpeg");
    m_mediaPlayer->setVideoDecoderPriority( _decoderlist );

    QtAV::VideoOutput _videoOutput;
    QtAV::VideoRendererId _widgetVideoRendererId = -1;
    _widgetVideoRendererId = QtAV::VideoRenderer::id("Widget");
    qDebug()<<"_widgetVideoRendererId:"<<_widgetVideoRendererId;

    if( _widgetVideoRendererId > 0 )
        m_videoOutput = new VideoOutput( _widgetVideoRendererId, this );
    else
        m_videoOutput = new VideoOutput(this);
    if (!m_videoOutput->widget()) {
//        QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
        return;
    }
    m_mediaPlayer->setRenderer(m_videoOutput);

    connect( m_mediaPlayer, &AVPlayer::durationChanged, this, &MediaPlayManager::slot_durationChanged );
    connect( m_mediaPlayer, &AVPlayer::positionChanged, this, &MediaPlayManager::slot_positionChanged );
    connect( m_mediaPlayer, &AVPlayer::stateChanged, this, &MediaPlayManager::slot_stateChanged );
}

MediaPlayManager::~MediaPlayManager()
{
    mediaPlayStop();
}

void MediaPlayManager::slot_durationChanged(qint64 duration)
{
    m_currentPlayDuration = duration;

    qDebug()<<"slot_durationChanged duration:"<<duration;
}

void MediaPlayManager::slot_positionChanged(qint64 position)
{
//     qDebug()<<"slot_positionChanged position:"<<position

     if( position >= (m_currentPlayDuration - 100) || m_currentPlayDuration < 0 )
     {
             emit signal_playOverThenNext();
     }
}

void MediaPlayManager::slot_stateChanged(QtAV::AVPlayer::State state)
{
    setPlayStatus( MUESIC_PLAY_STATUS(state) );
}

//参数 总时间百分比
void MediaPlayManager::skipPlayPercentage( const int _skipTime )
{
    if( m_mediaPlayer->state() ==  QtAV::AVPlayer::StoppedState )
        return;

    if( m_mediaPlayer == NULL )
        return;

    skipPlayTime( _skipTime*m_currentPlayDuration/1000 );
//    qDebug()<<"skipPlayPercentage _skipTime:"<<_skipTime;
}

//参数 毫秒数
void MediaPlayManager::skipPlayTime( const int _skipTime )
{
    if( m_mediaPlayer == NULL )
        return;

    if( m_mediaPlayer->state() ==  QtAV::AVPlayer::StoppedState )
        return;

//    m_mediaPlayer->setSeekType( AccurateSeek );
    m_mediaPlayer->seek( (qint64)_skipTime );
    qDebug()<<"MediaPlayManager _skipTime:"<<_skipTime;
}

void MediaPlayManager::setPlayStatus(const MUESIC_PLAY_STATUS _playStatus)
{
    currentPlayStatus = _playStatus;
}

void MediaPlayManager::mediaPlayStart(const QString &_url)
{
    qDebug()<<"mediaPlayStart url:"<<_url;

    if( _url.isEmpty() )
        return;

    mediaPlayStop();
    m_currentPlayURL = _url;

    m_mediaPlayer->play(_url);
}

void MediaPlayManager::mediaPlayOrPause()
{

    if ( !m_mediaPlayer->isPlaying() )
    {
        m_mediaPlayer->play();
        return;
    }

    m_mediaPlayer->pause(!m_mediaPlayer->isPaused());

}

void MediaPlayManager::mediaPlayStop()
{
    if( m_mediaPlayer != NULL )
    {
        m_mediaPlayer->stop();
    }

    m_play_flag = false;
    qDebug()<<"mediaPlayStop...";
}

void MediaPlayManager::setVolume(const int &_volume)
{
    m_currentVolume = _volume/1.0;

    if( m_mediaPlayer )
        m_mediaPlayer->audio()->setVolume( m_currentVolume/ECHO_MEDIA_MAX_VOLUME_NUM );
}

int MediaPlayManager::getVolume()
{
    return m_mediaPlayer->audio()->volume() * ECHO_MEDIA_MAX_VOLUME_NUM;
}