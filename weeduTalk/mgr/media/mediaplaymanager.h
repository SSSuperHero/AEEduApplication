#ifndef MEDIAPLAYMANAGER_H
#define MEDIAPLAYMANAGER_H

#include <QObject>
#include <QtAV/QtAV>
#include "config/define.h"
#include "mybasesingleton.h"

enum PLAY_SEEK_TYPE
{
    PLAY_SEEK_NONE,
    PLAY_SEEK_START,
    PLAY_SEEK_END
};

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
    void mediaPlayOrPause();
    void mediaPlayStop();
    void setVolume( const int &_volume );
    int getVolume();

    void skipPlayTime(const int _skipTime);
    void skipPlayPercentage( const int _skipTime );

    QWidget *startPlayMidea(const QString _videoFile);
    QWidget *startPlayMidea(const QString _videoFile, const int _startTime, const int _endTime);
    void mediaPause();
private:
//    QMediaPlayer                *m_echoMediaPlayer;
    QtAV::VideoOutput           *m_videoOutput;
    QtAV::AVPlayer              *m_mediaPlayer;
    QString                     m_currentPlayURL;
    double                      m_currentVolume;
    int                         m_playStartTime;
    int                         m_playEndTime;
    PLAY_SEEK_TYPE              m_seekType;

    qint64                      m_currentPlayDuration;
};

#endif // MEDIAPLAYMANAGER_H
