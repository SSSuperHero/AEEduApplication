#ifndef ECHOMEDIAMANAGER_H
#define ECHOMEDIAMANAGER_H

#include <QObject>
//#include "vlcmediamanager.h"
#include "echoparsewebmedia.h"
#include "utility/singleton.h"
#include "echomediahttprequest.h"
#include "echocurrplaylistmanager.h"
#include "echomediaplayer.h"
#include "mybasesingleton.h"

namespace  {
    const QString KEY_PLAYER_INFO  = "playerInfo";
}

struct playerConfigInfo
{
    QString                 soundId;
    int                     volume;
    int                     playType;
};

BEGIN_TO_JSON(playerConfigInfo)
MEMBER_TO_JSON(soundId)
MEMBER_TO_JSON(volume)
MEMBER_TO_JSON(playType)
END_TO_JSON()

BEGIN_FROM_JSON(playerConfigInfo)
MEMBER_FROM_JSON(soundId)
MEMBER_FROM_JSON(volume)
MEMBER_FROM_JSON(playType)
END_FROM_JSON()

class EchoMediaManager : public QObject
{
    Q_OBJECT

#ifdef Q_OS_MAC
    MY_DECLARE_SINGLETON(EchoMediaManager)
#else
    DECLARE_SINGLETON(EchoMediaManager)
    // SingletonMgrBase interface
#endif

public:
    explicit EchoMediaManager(QObject *parent = 0);

    void init();

    void mediaPlayStart(const QString &_url);
    void mediaPlayOrPause();
    void mediaPlayStop();
    void setVolume( const int &_volume );
    int getVolume();
    QString getCurrentPlayId();

    EchoCurrPlayListManager *getCurrentPlayListManager();
    QHash<QString, CurrPlaySoundItem> getCurrentPlayList();
    void mediaPlayCurrent();
    void setPlayStatus(const MUESIC_PLAY_STATUS _playStatus);
    MUESIC_PLAY_STATUS getPlayStatus();

    void setPlayType(const CURRING_PLAY_TYPE _playType);
    CURRING_PLAY_TYPE getPlayType();
    void setSoundIsLike(const QString &_songId, const int &_type);
    void updatePlayListItem(const soundInfoEntity &_soundInfo );
    void deletePlayListItem(const QString &id);

    void playSliderValueChanged( const int _value );
    void playerConfigInit();
    void insertPlayList(const CurrPlaySoundItem& item, int _insertId = 0 );

private:
    void insertPlayList(soundInfoEntity &_soundInfo, int _insertId = 0 );
    void writePlayerConfig();
    void isShowAddPlayListRemind( const int _soundId );
    void bellLogPlayStart(const echoBellEditInfo &_bellEditInfo);

public:
signals:
    void signal_updatePlayProgress( QString, int );
    void signal_startPlayMusic( const soundInfoEntity );
    void signal_updatePlayStates( const MUESIC_PLAY_STATUS _playState );
    void signal_webWidgetClose();

    void signal_soundPlayDo( int soundId, bool _remind = false );
    void signal_updateLikePic(const bool _likeFlag);
    void signal_changePlayType( const CURRING_PLAY_TYPE _playType );

    void signal_showAddPlayListRemind();

    void signal_playListClear();

public slots:
    void slot_bellPlayDo(int _bellId );
    void slot_bellLogPlayDo(int _bellId );
    void slot_soundPlayDo( const int &_soundId, bool _remind = false );
    void slot_addSoundToList(const int &_soundId);
    void slot_nextPlayTolist( const int &_soundId );
    void slot_soundPauseDo( int soundId );
    void slot_getSoundInfo( soundInfoEntity _soundInfo );
    void slot_getBellInfo( soundInfoEntity _bellInfo );
    void slot_getBellLogInfo(const echoBellEditInfo &_bellEditInfo ,
                             const soundInfoEntity &_soundInfo);
    void slot_addSoundPlayList( soundInfoEntity _soundInfo );
    void slot_nextPlaySound( soundInfoEntity _soundInfo );
    void slot_playOverThenNext( bool isClick =false );
    void slot_soundPlayListDo( QJsonArray _soundArr );
    void slot_getSoundsAllInfo( echoSoundsAllInfo_t _soundsAllInfo );
    void slot_videoPlayDo();

    void slot_clickePushButtonPlay();
    void slot_mediaPlayLast(bool isClick);
    void slot_mediaPlayNext();
    void slot_resetApplication();
private:
    EchoMediaPlayer             *m_MediaPlayerManager;
//    VlcMediaManager             *m_vlcMediaManager;

    EchoMediaHttpRequest        m_mediaHttpRequest;
    EchoCurrPlayListManager     *m_currPlayListManager;

    soundInfoEntity             m_currentSoundInfo;

    CURRING_PLAY_TYPE           m_currentPlayType;

    playerConfigInfo            m_playerConfigInfo;
    bool                        m_playerConfigInit;

};

#endif // ECHOMEDIAMANAGER_H
