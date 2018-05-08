#include "echomediahttprequest.h"
#include "utility/aes/echoaesutility.h"


EchoMediaHttpRequest::EchoMediaHttpRequest(QObject *parent) :
    QObject(parent),
    m_playId( 0 ),
    m_loadType( LOAD_SOUND_DOPLAY )
{

}

void EchoMediaHttpRequest::loadSoundInfo( const int &_soundId , const LOAD_SOUND_YUPE _loadType )
{
    m_loadType = _loadType;

    if( m_playId == _soundId )
    {
        loadHandle( m_songInfo.result, m_loadType );

        return;
    }

    m_playId = _soundId;
    soundInfoReply = EchoWebHttpApi::instance()->getSoundIdInfo( this, _soundId );

    connect(soundInfoReply, &EntityNetworkReplyHolder::signal_onFinish,
            this, &EchoMediaHttpRequest::slot_onLoadSoundInfoFinish);
    connect(soundInfoReply, &EntityNetworkReplyHolder::signal_onSuccess,
            this, &EchoMediaHttpRequest::slot_onLoadSoundInfoSuccess);
    connect(soundInfoReply, &EntityNetworkReplyHolder::signal_onFailure,
            this, &EchoMediaHttpRequest::slot_onLoadSoundInfoFailure);

}

void EchoMediaHttpRequest::loadHandle( const soundInfoEntity _soundInfo,
                                       const LOAD_SOUND_YUPE _loadType )
{
    switch ( _loadType )
    {
    case LOAD_SOUND_DOPLAY:
        emit signal_getSoundInfo( _soundInfo );
        break;

    case LOAD_SOUND_NEXT_DOPLAY:
        emit signal_nextPlaySound( _soundInfo );
        break;

    case LOAD_SOUND_ADD_TOLIST:
        emit signal_addSoundPlayList( _soundInfo );
        break;

    case LOAD_BELL_LOG_TRY_LISTEN:
        emit signal_getBellLogInfo( m_bellLogInfo, _soundInfo );
        break;
    default:
        break;
    }
}

void EchoMediaHttpRequest::slot_onLoadSoundInfoFinish()
{

}

void EchoMediaHttpRequest::slot_onLoadSoundInfoSuccess(const QString &response)
{
    fromJson( response, m_songInfo );

    loadHandle( m_songInfo.result, m_loadType );

    qDebug()<<"slot_onLoadSoundInfoSuccess url:" << m_songInfo.result.source;
}

void EchoMediaHttpRequest::slot_onLoadSoundInfoFailure(const BaseEntity &baseEntity)
{

}


void EchoMediaHttpRequest::loadSoundsAllInfo( const QString &_soundIds )
{
    soundsAllInfoReply = EchoWebHttpApi::instance()->getSoundsAllIdInfo( this, _soundIds );

    connect(soundsAllInfoReply, &EntityNetworkReplyHolder::signal_onSuccess,
            this, &EchoMediaHttpRequest::slot_onLoadSoundsAllInfoSuccess);
    connect(soundsAllInfoReply, &EntityNetworkReplyHolder::signal_onFailure,
            this, &EchoMediaHttpRequest::slot_onLoadSoundsAllInfoFailure);
}

void EchoMediaHttpRequest::slot_onLoadSoundsAllInfoSuccess( const QString &response )
{
    HttpEntity<EchoSoundsAllInfo> _soundsAllInfo;
    fromJson( response, _soundsAllInfo );

    emit signal_getSoundsAllInfo( _soundsAllInfo.result.list );

//    if( _soundsAllInfo.result.list.size() > 1 )
//        emit signal_getSoundInfo( _soundsAllInfo.result.list.at(0) );
}

void EchoMediaHttpRequest::slot_onLoadSoundsAllInfoFailure(const BaseEntity &baseEntity)
{

}

void EchoMediaHttpRequest::echoBellTryListen( const int &_bellId )
{
    m_playId = _bellId;
    loadBellIsBuy( _bellId );
}

void EchoMediaHttpRequest::loadBellIsBuy( const int &_bellId )
{
    m_getBellIsbuyReply = EchoWebHttpApi::instance()->getBellBySoundId( this, _bellId );

    connect(m_getBellIsbuyReply, &EntityNetworkReplyHolder::signal_onSuccess,
            this, &EchoMediaHttpRequest::slot_onLoadBellIsBuySuccess);
    connect(m_getBellIsbuyReply, &EntityNetworkReplyHolder::signal_onFailure,
            this, &EchoMediaHttpRequest::slot_onLoadBellIsBuyFailure);

}

void EchoMediaHttpRequest::slot_onLoadBellIsBuySuccess( const QString &response )
{
    HttpEntity<echoBellInfo> _bellInfo;
    fromJson( response, _bellInfo );

    loadBellTryListen( m_playId, _bellInfo.result.is_buy );
}

void EchoMediaHttpRequest::slot_onLoadBellIsBuyFailure(const BaseEntity &baseEntity)
{

}

void EchoMediaHttpRequest::loadBellTryListen( const int &_bellId, const int &_isBuy )
{
    soundsAllInfoReply = EchoWebHttpApi::instance()->bellTryListen( this, _bellId, _isBuy );

    connect(soundsAllInfoReply, &EntityNetworkReplyHolder::signal_onSuccess,
            this, &EchoMediaHttpRequest::slot_onLoadBellTryListenSuccess);
    connect(soundsAllInfoReply, &EntityNetworkReplyHolder::signal_onFailure,
            this, &EchoMediaHttpRequest::slot_onLoadBellTryListenFailure);
}

void EchoMediaHttpRequest::slot_onLoadBellTryListenSuccess( const QString &response )
{
    HttpEntity<bellInfoEntity> _bellInfo;
    fromJson( response, _bellInfo );

    if( _bellInfo.result.source.isEmpty() )
        return;

    soundInfoEntity _soundInfo;

    _soundInfo.source = EchoAesUtility::aes_decrypt_bellUrl( _bellInfo.result.source );
    _soundInfo.pic_100 = _bellInfo.result.pic;
    _soundInfo.name = _bellInfo.result.name;

    qDebug()<<"slot_onLoadBellTryListenSuccess url:" << _soundInfo.source;

    emit signal_getBellInfo( _soundInfo );
}

void EchoMediaHttpRequest::slot_onLoadBellTryListenFailure(const BaseEntity &baseEntity)
{

}

//获取铃声记录信息
void EchoMediaHttpRequest::getBellEditInfo( const int _bellEditId )
{
    m_getBellEditInfoReply = EchoWebHttpApi::getBellEditLogInfo( this, _bellEditId );

    connect(m_getBellEditInfoReply, &EntityNetworkReplyHolder::signal_onSuccess,
            this, &EchoMediaHttpRequest::slot_onGetBellEditInfoSuccess);
    connect(m_getBellEditInfoReply, &EntityNetworkReplyHolder::signal_onFailure,
            this, &EchoMediaHttpRequest::slot_onGetBellEditInfoFailure);
}
void EchoMediaHttpRequest::slot_onGetBellEditInfoSuccess(const QString &response)
{
    HttpEntity<echoBellEditInfo> _beelEditInfoEntity;
    fromJson( response, _beelEditInfoEntity );

    m_bellLogInfo = _beelEditInfoEntity.result;
    loadSoundInfo( m_bellLogInfo.sound_id, LOAD_BELL_LOG_TRY_LISTEN );
//    emit signal_getBellLogInfo( _beelEditInfoEntity.result );
}

void EchoMediaHttpRequest::slot_onGetBellEditInfoFailure(const BaseEntity &baseEntity)
{

}
