#ifndef VLCMEDIAMANAGER_H
#define VLCMEDIAMANAGER_H

#include <QObject>
#include <QTimer>
#include "vlc/vlc.h"
#include "vlc/libvlc.h"
#include "config/define.h"

class VlcMediaManager : public QObject
{
    Q_OBJECT
//    DECLARE_SINGLETON(VlcMediaManager)

public:
    explicit VlcMediaManager(QObject *parent = 0);

    void init();

    ~VlcMediaManager();
signals:
    void playStateUpdate(const MUESIC_PLAY_STATUS);
    void updatePlayProgress( QString, int );
    void signal_playOverThenNext(bool isClick);
public slots:
//    void pause_play();
    void updatePalyTime();
public:
    void mediaPlayStart(const QString &_url);
    void mediaPlayOrPause();
    void mediaPlayStop();
    void setVolume( const int &_volume );
    int getVolume();

    void setPlayStatus( const MUESIC_PLAY_STATUS _playStatus );
    MUESIC_PLAY_STATUS getPlayStatus();
public:
    bool m_play_flag;
    qreal m_progress;
    QString m_playTimeText;
    void skipPlayTime(const int _skipTime);
    void skipPlayPercentage( const int _skipTime );
    void bellLogPlayStart(const QString &_url, const QString &_startTime, const QString &_endTime);

private:
    void init_mediaPlayer(const char* url);
private:
    QTimer*                     m_pause_play;
    QString                     m_currentPlayURL;
    QTimer*                     m_updatePalyTimer;
    libvlc_instance_t *         m_mediaInstance;  //libvlc的实例
    libvlc_media_player_t *     m_mediaPlayer;
    libvlc_media_t *            m_mediaExpression;
    bool                        m_playOverFlag;
    bool                        m_pause_flag;

    int                         m_currentVolume;
    MUESIC_PLAY_STATUS          currentPlayStatus;

    bool                        m_bellLogPlayFlag;
    int                         m_bellStartTime;
    int                         m_bellEndTime;
};

#endif // VLCMEDIAMANAGER_H
