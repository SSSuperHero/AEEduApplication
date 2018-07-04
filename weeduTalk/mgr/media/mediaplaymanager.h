#ifndef MEDIAPLAYMANAGER_H
#define MEDIAPLAYMANAGER_H

#include <QObject>
#include <QtAV/QtAV>
#include "config/define.h"
#include "mybasesingleton.h"

class MediaPlayManager : public QObject
{
    Q_OBJECT

    MY_DECLARE_SINGLETON(MediaPlayManager)

public:
    MediaPlayManager(QObject *parent = nullptr);

    void init();

    ~MediaPlayManager();
signals:
    void signal_playOverThenNext();
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
public:
    void skipPlayTime(const int _skipTime);
    void skipPlayPercentage( const int _skipTime );

private:
//    QMediaPlayer                *m_echoMediaPlayer;
    QtAV::VideoOutput           *m_videoOutput;
    QtAV::AVPlayer              *m_mediaPlayer;

    QString                     m_currentPlayURL;
//    QTimer*                     m_updatePalyTimer;
    bool                        m_playOverFlag;
    bool                        m_pause_flag;
    bool                        m_play_flag;
    qreal                       m_progress;
    QString                     m_playTimeText;

    double                      m_currentVolume;
    MUESIC_PLAY_STATUS          currentPlayStatus;

    qint64                      m_currentPlayDuration;
};

#endif // MEDIAPLAYMANAGER_H
