#ifndef ECHOMEDIAPLAYER_H
#define ECHOMEDIAPLAYER_H

#include <QObject>
//#include <QtMultimedia>
#include <QtAV/QtAV>
#include "config/define.h"


class EchoMediaPlayer : public QObject
{
    Q_OBJECT
public:
    explicit EchoMediaPlayer(QObject *parent = nullptr);

    void init();

    ~EchoMediaPlayer();
signals:
    void playStateUpdate(const MUESIC_PLAY_STATUS);
    void updatePlayProgress( QString, int );
    void signal_playOverThenNext(bool isClick);
public slots:
    void slot_durationChanged(qint64 duration);
    void slot_positionChanged(qint64 position);
    void slot_stateChanged(QtAV::AVPlayer::State state);

public:
    void mediaPlayStart(const QString &_url);
    void mediaPlayOrPause();
    void mediaPlayStop();
    void setVolume( const int &_volume );
    int getVolume();

    void setPlayStatus( const MUESIC_PLAY_STATUS _playStatus );
    MUESIC_PLAY_STATUS getPlayStatus();
public:
    void skipPlayTime(const int _skipTime);
    void skipPlayPercentage( const int _skipTime );
    void bellLogPlayStart(const QString &_url, const QString &_startTime, const QString &_endTime);

private:
    void init_mediaPlayer(const char* url);

private:
//    QMediaPlayer                *m_echoMediaPlayer;
    QtAV::VideoOutput           *m_videoOutput;
    QtAV::AVPlayer              *m_echoMediaPlayer;

    QString                     m_currentPlayURL;
//    QTimer*                     m_updatePalyTimer;
    bool                        m_playOverFlag;
    bool                        m_pause_flag;
    bool                        m_play_flag;
    qreal                       m_progress;
    QString                     m_playTimeText;

    double                      m_currentVolume;
    MUESIC_PLAY_STATUS          currentPlayStatus;

    bool                        m_bellLogPlayFlag;
    bool                        m_bellskipFlag;
    int                         m_bellStartTime;
    int                         m_bellEndTime;

    qint64                      m_currentPlayDuration;
};

#endif // ECHOMEDIAPLAYER_H
