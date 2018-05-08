#ifndef ECHOMEDIAHTTPREQUEST_H
#define ECHOMEDIAHTTPREQUEST_H

#include <QObject>
#include "utility/jsonutil.h"
#include "mgr/http/echowebhttpapi.h"

enum LOAD_SOUND_YUPE
{
    LOAD_SOUND_DOPLAY = 0,
    LOAD_SOUND_NEXT_DOPLAY,
    LOAD_SOUND_ADD_TOLIST,
    LOAD_BELL_TRY_LISTEN,
    LOAD_BELL_LOG_TRY_LISTEN
};

//播放一首
struct soundInfoEntity
{
    QString id;
    QString source;
    QString name;
    int length;
    int is_like;
    QString pic_100;
};

BEGIN_FROM_JSON(soundInfoEntity)
MEMBER_FROM_JSON(id)
MEMBER_FROM_JSON(source)
MEMBER_FROM_JSON(name)
MEMBER_FROM_JSON(length)
MEMBER_FROM_JSON(is_like)
MEMBER_FROM_JSON(pic_100)
END_FROM_JSON()

//一键播放请求
typedef QVector<soundInfoEntity> echoSoundsAllInfo_t;

struct EchoSoundsAllInfo
{
    echoSoundsAllInfo_t list;
};

BEGIN_FROM_JSON(EchoSoundsAllInfo)
MEMBER_FROM_JSON(list)
END_FROM_JSON()


struct bellInfoEntity
{
    QString name;
    QString pic;
    QString source;
};
BEGIN_FROM_JSON(bellInfoEntity)
MEMBER_FROM_JSON(name)
MEMBER_FROM_JSON(pic)
MEMBER_FROM_JSON(source)
END_FROM_JSON()

class EchoMediaHttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit EchoMediaHttpRequest(QObject *parent = 0);

    void loadSoundInfo( const int &_soundId, const LOAD_SOUND_YUPE _loadType = LOAD_SOUND_DOPLAY );
    void loadSoundsAllInfo( const QString &_soundIds );
    void getBellEditInfo(const int _bellEditId);
    void echoBellTryListen( const int &_bellId );

private:
    void loadHandle(const soundInfoEntity _soundInfo, const LOAD_SOUND_YUPE _loadType);
    void loadBellIsBuy(const int &_bellId);
    void loadBellTryListen( const int &_bellId, const int &_isBuy );

public:
signals:
    void signal_getSoundInfo( soundInfoEntity _soundInfo );
    void signal_addSoundPlayList( soundInfoEntity _soundInfo );
    void signal_nextPlaySound( soundInfoEntity _soundInfo );
    void signal_getSoundsAllInfo( echoSoundsAllInfo_t _soundsAllInfo );
    void signal_getBellInfo( soundInfoEntity _bellInfo );

    void signal_getBellLogInfo( const echoBellEditInfo &_bellInfo,
                                const soundInfoEntity &_soundInfo);

public slots:
    void slot_onLoadSoundInfoFinish();
    void slot_onLoadSoundInfoSuccess(const QString& response);
    void slot_onLoadSoundInfoFailure(const BaseEntity& baseEntity);

    void slot_onLoadSoundsAllInfoSuccess(const QString& response);
    void slot_onLoadSoundsAllInfoFailure(const BaseEntity& baseEntity);

protected slots:
    void slot_onLoadBellTryListenFailure(const BaseEntity &baseEntity);
    void slot_onLoadBellTryListenSuccess(const QString &response);

    void slot_onGetBellEditInfoSuccess(const QString &response);
    void slot_onGetBellEditInfoFailure(const BaseEntity &baseEntity);

    void slot_onLoadBellIsBuySuccess(const QString &response);
    void slot_onLoadBellIsBuyFailure(const BaseEntity &baseEntity);

private:
    EntityNetworkReplyHolder    *soundInfoReply;
    EntityNetworkReplyHolder    *soundsAllInfoReply;
    EntityNetworkReplyHolder    *m_getBellEditInfoReply;
    EntityNetworkReplyHolder    *m_getBellIsbuyReply;

    int                         m_playId;
    HttpEntity<soundInfoEntity> m_songInfo;
    echoBellEditInfo            m_bellLogInfo;

    LOAD_SOUND_YUPE             m_loadType;

};

#endif // ECHOMEDIAHTTPREQUEST_H
