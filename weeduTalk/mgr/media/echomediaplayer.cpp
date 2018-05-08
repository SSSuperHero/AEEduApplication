#include "echomediaplayer.h"
#include "utility/stringutility.h"
#include <QMessageBox>


using namespace QtAV;
EchoMediaPlayer::EchoMediaPlayer(QObject *parent) :
    QObject(parent),
    m_echoMediaPlayer(NULL),
    m_currentPlayDuration(0),
    m_playOverFlag(false),
    m_bellskipFlag(false),
    m_currentVolume(50.0),
    currentPlayStatus(MUESIC_PLAY_NONE),
    m_bellLogPlayFlag( false )
{
    init();
}

void EchoMediaPlayer::init()
{
    m_echoMediaPlayer = new AVPlayer(this);

    QStringList _decoderlist;
//    _decoderlist.append("dxva");
    _decoderlist.append("FFmpeg");
    m_echoMediaPlayer->setVideoDecoderPriority( _decoderlist );

    QtAV::VideoOutput _videoOutput;
    QtAV::VideoRendererId _widgetVideoRendererId = -1;
    _widgetVideoRendererId = QtAV::VideoRenderer::id("Widget");
    qDebug()<<"_widgetVideoRendererId:"<<_widgetVideoRendererId;

    if( _widgetVideoRendererId > 0 )
        m_videoOutput = new VideoOutput( _widgetVideoRendererId, this );
    else
        m_videoOutput = new VideoOutput(this);
    if (!m_videoOutput->widget()) {
        QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
        return;
    }
    m_echoMediaPlayer->setRenderer(m_videoOutput);

    connect( m_echoMediaPlayer, &AVPlayer::durationChanged, this, &EchoMediaPlayer::slot_durationChanged );
    connect( m_echoMediaPlayer, &AVPlayer::positionChanged, this, &EchoMediaPlayer::slot_positionChanged );
    connect( m_echoMediaPlayer, &AVPlayer::stateChanged, this, &EchoMediaPlayer::slot_stateChanged );
}

EchoMediaPlayer::~EchoMediaPlayer()
{
    mediaPlayStop();
}

void EchoMediaPlayer::slot_durationChanged(qint64 duration)
{
    m_currentPlayDuration = duration;

    if( duration > 0 )
        m_play_flag = true;
    else if( m_play_flag )
        emit signal_playOverThenNext( true );

    qDebug()<<"slot_durationChanged duration:"<<duration;
}

void EchoMediaPlayer::slot_positionChanged(qint64 position)
{
//     qDebug()<<"slot_positionChanged position:"<<position;

     QString curtimestr,durationstr;

     curtimestr = StringUtility::timeTostring( position/1000 );

     durationstr = StringUtility::timeTostring( m_currentPlayDuration/1000 );
     if( m_currentPlayDuration > 0 )
     {
         m_progress = ( position*1000.0)/(m_currentPlayDuration*1.0 );
         m_playTimeText = curtimestr+"/"+durationstr;
     }

     emit updatePlayProgress( m_playTimeText, (int)m_progress );

     //铃声
     if( m_bellskipFlag )
     {
//         qDebug()<<"slot_durationChanged m_bellStartTime m_bellEndTime"<<m_bellStartTime<<m_bellEndTime;
         m_bellskipFlag = false;
         skipPlayTime( m_bellStartTime*1000 );
     }

     if( position >= (m_currentPlayDuration - 1000) ||
         m_currentPlayDuration < 0 ||
         ( m_bellLogPlayFlag && position/1000 >= m_bellEndTime ) )
     {
         {
             if( m_bellLogPlayFlag )
                 m_bellLogPlayFlag = false;

             emit signal_playOverThenNext( true );

             return;
         }
     }
}

void EchoMediaPlayer::slot_stateChanged(QtAV::AVPlayer::State state)
{
    setPlayStatus( MUESIC_PLAY_STATUS(state) );
}

//参数 总时间百分比
void EchoMediaPlayer::skipPlayPercentage( const int _skipTime )
{
    if( m_echoMediaPlayer->state() ==  QtAV::AVPlayer::StoppedState )
        return;

    if( m_echoMediaPlayer == NULL )
        return;

    skipPlayTime( _skipTime*m_currentPlayDuration/1000 );
//    qDebug()<<"skipPlayPercentage _skipTime:"<<_skipTime;
}

//参数 毫秒数
void EchoMediaPlayer::skipPlayTime( const int _skipTime )
{
    if( m_echoMediaPlayer == NULL )
        return;

    if( m_echoMediaPlayer->state() ==  QtAV::AVPlayer::StoppedState )
        return;

//    m_echoMediaPlayer->setSeekType( AccurateSeek );
    m_echoMediaPlayer->seek( (qint64)_skipTime );
    qDebug()<<"EchoMediaPlayer _skipTime:"<<_skipTime;
}

void EchoMediaPlayer::setPlayStatus(const MUESIC_PLAY_STATUS _playStatus)
{
    currentPlayStatus = _playStatus;
    emit playStateUpdate( _playStatus );
}

MUESIC_PLAY_STATUS EchoMediaPlayer::getPlayStatus()
{
    return currentPlayStatus;
}

void EchoMediaPlayer::bellLogPlayStart( const QString &_url, const QString &_startTime,
                                        const QString &_endTime )
{
    mediaPlayStart( _url );

    m_bellLogPlayFlag = true;
    m_bellskipFlag = true;

    m_bellStartTime = _startTime.toFloat();
    m_bellEndTime = _endTime.toFloat();

//    qDebug()<<"bellLogPlayStart m_bellStartTime m_bellEndTime"<<m_bellStartTime<<m_bellEndTime;
}

void EchoMediaPlayer::mediaPlayStart(const QString &_url)
{
    qDebug()<<"mediaPlayStart url:"<<_url;

    mediaPlayStop();
    m_currentPlayURL = _url;

    m_echoMediaPlayer->play(_url);
}

void EchoMediaPlayer::mediaPlayOrPause()
{

    if ( !m_echoMediaPlayer->isPlaying() )
    {
        m_echoMediaPlayer->play();
        return;
    }

    m_echoMediaPlayer->pause(!m_echoMediaPlayer->isPaused());

}

void EchoMediaPlayer::mediaPlayStop()
{
    if( m_echoMediaPlayer != NULL )
    {
        m_echoMediaPlayer->stop();
    }

    m_play_flag = false;
    qDebug()<<"mediaPlayStop...";
}

void EchoMediaPlayer::setVolume(const int &_volume)
{
    m_currentVolume = _volume/1.0;

    if( m_echoMediaPlayer )
        m_echoMediaPlayer->audio()->setVolume( m_currentVolume/ECHO_MEDIA_MAX_VOLUME_NUM );
}

int EchoMediaPlayer::getVolume()
{
    return m_echoMediaPlayer->audio()->volume() * ECHO_MEDIA_MAX_VOLUME_NUM;
}
