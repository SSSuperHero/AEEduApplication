#include "echomediamanager.h"
#include "utility/stringutility.h"
#include "config/configutil.h"

EchoMediaManager::EchoMediaManager(QObject *parent) :
    QObject(parent),
    m_MediaPlayerManager(NULL),
    m_currPlayListManager(NULL),
    m_currentPlayType( PLAYING_MUESIC_LOOP_ALL ),
    m_playerConfigInit( true )
{
    m_playerConfigInfo.volume = 50;
    m_playerConfigInfo.soundId = "0";
    m_playerConfigInfo.playType = PLAYING_MUESIC_LOOP_ALL;
}

void EchoMediaManager::init()
{
    connect( this, &EchoMediaManager::signal_soundPlayDo,
             this, &EchoMediaManager::slot_soundPlayDo );

    m_MediaPlayerManager = new EchoMediaPlayer();
    connect( m_MediaPlayerManager, &EchoMediaPlayer::signal_playOverThenNext,
             this, &EchoMediaManager::slot_playOverThenNext );
    connect( m_MediaPlayerManager, &EchoMediaPlayer::updatePlayProgress,
             this, &EchoMediaManager::signal_updatePlayProgress );
    connect( m_MediaPlayerManager, &EchoMediaPlayer::playStateUpdate,
             this, &EchoMediaManager::signal_updatePlayStates );

    connect( &m_mediaHttpRequest, &EchoMediaHttpRequest::signal_getSoundInfo,
             this, &EchoMediaManager::slot_getSoundInfo );
    connect( &m_mediaHttpRequest, &EchoMediaHttpRequest::signal_getBellInfo,
             this, &EchoMediaManager::slot_getBellInfo );
    connect( &m_mediaHttpRequest, &EchoMediaHttpRequest::signal_getBellLogInfo,
             this, &EchoMediaManager::slot_getBellLogInfo );
    connect( &m_mediaHttpRequest, &EchoMediaHttpRequest::signal_getSoundsAllInfo,
             this, &EchoMediaManager::slot_getSoundsAllInfo );
    connect( &m_mediaHttpRequest, &EchoMediaHttpRequest::signal_addSoundPlayList,
             this, &EchoMediaManager::slot_addSoundPlayList );
    connect( &m_mediaHttpRequest, &EchoMediaHttpRequest::signal_nextPlaySound,
             this, &EchoMediaManager::slot_nextPlaySound );

    m_currPlayListManager = new EchoCurrPlayListManager();
    connect( m_currPlayListManager, &EchoCurrPlayListManager::signal_playListClear,
             this, &EchoMediaManager::signal_playListClear );

//    playerConfigInit();
}

void EchoMediaManager::playerConfigInit()
{

    QString jsonPlayerConfig = ConfigUtil::value(KEY_PLAYER_INFO, "").toString();
    if ( !jsonPlayerConfig.isEmpty() )
    {
        fromJson( jsonPlayerConfig, m_playerConfigInfo );
    }

    setVolume( m_playerConfigInfo.volume );
    setPlayType( (CURRING_PLAY_TYPE)m_playerConfigInfo.playType );

    int _soundId = 0;
    if( m_currPlayListManager->findPlayItem( m_playerConfigInfo.soundId ) )
        _soundId =  m_playerConfigInfo.soundId.toInt();
    else
        _soundId =  m_currPlayListManager->getCurrentPlayId().toInt();

    if( _soundId > 0 )
    {
        m_playerConfigInit = false;
        emit signal_soundPlayDo( _soundId );
    }

}

void EchoMediaManager::writePlayerConfig()
{
    QString jsonPlayerConfig = toJson( m_playerConfigInfo );
    ConfigUtil::setValue( KEY_PLAYER_INFO, jsonPlayerConfig );
}

void EchoMediaManager::isShowAddPlayListRemind( const int _soundId )
{
    if( _soundId == m_currPlayListManager->getCurrentPlayId().toInt() )
        return;

    emit signal_showAddPlayListRemind();
}

void EchoMediaManager::slot_bellPlayDo( int _bellId )
{
    m_mediaHttpRequest.echoBellTryListen( _bellId );
}

void EchoMediaManager::slot_bellLogPlayDo(int _bellId)
{
    m_mediaHttpRequest.getBellEditInfo( _bellId );
}

void EchoMediaManager::mediaPlayStart(const QString &_url)
{
    m_MediaPlayerManager->mediaPlayStart( _url );
}

void EchoMediaManager::slot_clickePushButtonPlay()
{

    switch ( getPlayStatus() )
    {
    case MUESIC_PLAY_NONE:
    case MUESIC_PLAY_STOP:
        mediaPlayCurrent();
        break;

    case MUESIC_PLAYING_START:
    case MUESIC_PLAY_PAUSE:
        mediaPlayOrPause();
        break;
    default:
        break;
    }
}

void EchoMediaManager::mediaPlayOrPause()
{
    m_MediaPlayerManager->mediaPlayOrPause();
}

void EchoMediaManager::mediaPlayStop()
{
    m_MediaPlayerManager->mediaPlayStop();
}

void EchoMediaManager::slot_mediaPlayLast( bool isClick )
{
    QString _playId = 0;

    CURRING_PLAY_TYPE _crrType = getPlayType();
    if( !isClick && _crrType == PLAYING_MUESIC_LOOP_ONE )
        _crrType = PLAYING_MUESIC_LOOP_ALL;

    switch ( _crrType )
    {
    case PLAYING_MUESIC_LOOP_ALL:
            m_currPlayListManager->getLastPlayItem( _playId );
        break;

    case PLAYING_MUESIC_LOOP_ONE:
            _playId = m_currPlayListManager->getCurrentPlayId();
        break;

    case PLAYING_MUESIC_RANDOM:
            m_currPlayListManager->getRandomPlayItem( _playId );
        break;
    default:
        break;
    }

    if( _playId.toInt() > 0 )
        emit signal_soundPlayDo( _playId.toInt() );
}

void EchoMediaManager::slot_mediaPlayNext()
{
    QString _playId("0");

    m_currPlayListManager->getNextPlayItem( _playId );

    if( _playId.toInt() > 0 )
        emit signal_soundPlayDo( _playId.toInt() );
}

void EchoMediaManager::slot_resetApplication()
{
    m_MediaPlayerManager->mediaPlayStop();
}

void EchoMediaManager::mediaPlayCurrent()
{
    QString _playId("0");

    _playId = m_currPlayListManager->getCurrentPlayId();

    if( _playId.toInt() > 0 )
        emit signal_soundPlayDo( _playId.toInt() );

    qDebug()<<"mediaPlayCurrent _playId:"<<_playId;
}

void EchoMediaManager::setVolume(const int &_volume)
{
    m_MediaPlayerManager->setVolume( _volume );
    m_playerConfigInfo.volume = _volume;
    writePlayerConfig();
}

int EchoMediaManager::getVolume()
{
    return m_MediaPlayerManager->getVolume();
}

QString EchoMediaManager::getCurrentPlayId()
{
    return m_currPlayListManager->getCurrentPlayId();
}

EchoCurrPlayListManager *EchoMediaManager::getCurrentPlayListManager()
{
    return m_currPlayListManager;
}

QHash<QString, CurrPlaySoundItem> EchoMediaManager::getCurrentPlayList()
{
    return m_currPlayListManager->getCurrentPlayMap();
}

void EchoMediaManager::setPlayStatus(const MUESIC_PLAY_STATUS _playStatus)
{
    m_MediaPlayerManager->setPlayStatus( _playStatus );
}

MUESIC_PLAY_STATUS EchoMediaManager::getPlayStatus()
{
    return m_MediaPlayerManager->getPlayStatus();
}

void EchoMediaManager::setPlayType(const CURRING_PLAY_TYPE _playType)
{
    m_currentPlayType = _playType;
    m_playerConfigInfo.playType = _playType;
    writePlayerConfig();

    emit signal_changePlayType( _playType );
}

CURRING_PLAY_TYPE EchoMediaManager::getPlayType()
{
    return m_currentPlayType;
}

void EchoMediaManager::slot_soundPlayDo( const int &_soundId, bool _remind )
{
    if( _remind )
        isShowAddPlayListRemind( _soundId );

    if( _soundId == m_currPlayListManager->getCurrentPlayId().toInt() &&
            getPlayType() != PLAYING_MUESIC_LOOP_ONE &&
            getPlayStatus() == MUESIC_PLAYING_START )
    {
        qDebug()<<"slot_soundPlayDo getPlayStatus:" << getPlayStatus();
        return;
    }

    if( _soundId == m_currPlayListManager->getCurrentPlayId().toInt() &&
            getPlayStatus() == MUESIC_PLAY_PAUSE )
    {
        m_MediaPlayerManager->mediaPlayOrPause();
        return;
    }

    qDebug()<<"slot_soundPlayDo _soundId:" << _soundId;
    m_currPlayListManager->setCurrentPlayId( _soundId );
    m_mediaHttpRequest.loadSoundInfo( _soundId, LOAD_SOUND_DOPLAY );

    m_playerConfigInfo.soundId = m_currPlayListManager->getCurrentPlayId();
    writePlayerConfig();
}

void EchoMediaManager::slot_addSoundToList(const int &_soundId)
{
    m_mediaHttpRequest.loadSoundInfo( _soundId, LOAD_SOUND_ADD_TOLIST );
//    m_playerConfigInit = true;
    isShowAddPlayListRemind( _soundId );
}

void EchoMediaManager::slot_nextPlayTolist(const int &_soundId)
{
    m_mediaHttpRequest.loadSoundInfo( _soundId, LOAD_SOUND_NEXT_DOPLAY );
}

void EchoMediaManager::slot_soundPauseDo( int soundId )
{
    if( getPlayStatus() != MUESIC_PLAYING_START )
        return;

    if( soundId != m_currPlayListManager->getCurrentPlayId().toInt() )
        return;

    m_MediaPlayerManager->mediaPlayOrPause();
}

void EchoMediaManager::slot_getSoundInfo( soundInfoEntity _soundInfo )
{
    m_currentSoundInfo = _soundInfo;

    if( m_playerConfigInit )
        mediaPlayStart( _soundInfo.source );
    else
        m_playerConfigInit = true;

    insertPlayList( _soundInfo );
    emit signal_startPlayMusic( _soundInfo );
}

void EchoMediaManager::slot_getBellInfo( soundInfoEntity _bellInfo)
{
    mediaPlayStart( _bellInfo.source );

    emit signal_startPlayMusic( _bellInfo );
}

void EchoMediaManager::bellLogPlayStart( const echoBellEditInfo &_bellEditInfo )
{
    m_MediaPlayerManager->bellLogPlayStart( _bellEditInfo.sound_source, _bellEditInfo.start_time,
                                         _bellEditInfo.end_time );
}

void EchoMediaManager::slot_getBellLogInfo( const echoBellEditInfo &_bellEditInfo,
                                            const soundInfoEntity &_soundInfo )
{
    bellLogPlayStart( _bellEditInfo );

    emit signal_startPlayMusic( _soundInfo );
}

void EchoMediaManager::slot_addSoundPlayList( soundInfoEntity _soundInfo )
{
    insertPlayList( _soundInfo );
}

void EchoMediaManager::slot_nextPlaySound( soundInfoEntity _soundInfo )
{
    QString _id = m_currPlayListManager->getCurrentPlayId();
    insertPlayList( _soundInfo, _id.toInt() );

    isShowAddPlayListRemind( _soundInfo.id.toInt() );
}

void EchoMediaManager::slot_playOverThenNext(bool isClick)
{
    QString _playId("0");
    CURRING_PLAY_TYPE _crrType;

    _crrType = getPlayType();
    if( !isClick && _crrType == PLAYING_MUESIC_LOOP_ONE )
        _crrType = PLAYING_MUESIC_LOOP_ALL;

    switch ( _crrType )
    {
    case PLAYING_MUESIC_LOOP_ALL:
            m_currPlayListManager->getNextPlayItem( _playId );
        break;

    case PLAYING_MUESIC_LOOP_ONE:
            _playId = m_currPlayListManager->getCurrentPlayId();
        break;

    case PLAYING_MUESIC_RANDOM:
            m_currPlayListManager->getRandomPlayItem( _playId );
        break;
    default:
        break;
    }

    if( _playId.toInt() > 0 )
        emit signal_soundPlayDo( _playId.toInt() );
}

void EchoMediaManager::slot_soundPlayListDo(QJsonArray _soundArr)
{
    if( _soundArr.size() < 1 )
        return;

    QString _idList;
    for( int i = 0; i < _soundArr.size(); i++ )
    {
        QString _tempStr = QString::number( _soundArr.at(i).toInt() );
        if( _idList.indexOf( _tempStr ) >= 0 )
            continue;
        if(i != _soundArr.size()-1 )
        {
            _tempStr += QString(",");
        }
        _idList += _tempStr;
    }

    m_mediaHttpRequest.loadSoundsAllInfo( _idList );
}

void EchoMediaManager::slot_getSoundsAllInfo(echoSoundsAllInfo_t _soundsAllInfo)
{
    if( _soundsAllInfo.size() < 1 )
        return;

    foreach ( soundInfoEntity _soundsItemInfo, _soundsAllInfo )
    {
        insertPlayList( _soundsItemInfo );
    }

    emit signal_soundPlayDo( _soundsAllInfo.at(0).id.toInt(), true );
//    isShowAddPlayListRemind( _soundsAllInfo.at(0).id.toInt() );
}

void EchoMediaManager::slot_videoPlayDo()
{
    slot_soundPauseDo( m_currPlayListManager->getCurrentPlayId().toInt() );
}

void EchoMediaManager::insertPlayList( soundInfoEntity &_soundInfo, int _insertId )
{
    if( m_currPlayListManager->findPlayItem( _soundInfo.id ) )
    {
        CurrPlaySoundItem _item = m_currPlayListManager->getPlayItem( _soundInfo.id );
        _soundInfo.is_like = _item.isLike;

        if( _insertId > 0 )
        {
            m_currPlayListManager->deletePlayItem( _soundInfo.id );
        }
        else
        {
            return;
        }
    }

    CurrPlaySoundItem item;
    item.id = _soundInfo.id;
    item.name = _soundInfo.name;
    item.isLike = _soundInfo.is_like;
    item.len = StringUtility::timeTostring( _soundInfo.length );
    qDebug()<<"item.len: _soundInfo.length:" << item.len << _soundInfo.length;

    if( !m_currPlayListManager->findPlayItem( _soundInfo.id ) )
    {
        m_currPlayListManager->insertPlayItem( item, QString::number(_insertId) );
//        m_currPlayListManager->write_catch_data();
    }
}

void EchoMediaManager::insertPlayList(const CurrPlaySoundItem &item, int _insertId)
{
    if( m_currPlayListManager->findPlayItem( item.id ) )
        return;

    m_currPlayListManager->insertPlayItem( item, QString::number(_insertId) );
//    m_currPlayListManager->write_catch_data();
}

void EchoMediaManager::setSoundIsLike( const QString &_songId, const int &_type )
{
    if( m_currPlayListManager->findPlayItem( _songId ) )
    {
        CurrPlaySoundItem item = m_currPlayListManager->getPlayItem( _songId );
        item.isLike = _type;
        m_currPlayListManager->updatePlayItem( item );
    }
    qDebug()<<"setSoundIsLike _songId _type:"<<_songId<<_type;

    EchoWebHttpApi::instance()->postIsLike( this, _songId, _type );

    if( _songId == m_currPlayListManager->getCurrentPlayId() )
        emit signal_updateLikePic( _type );
}

void EchoMediaManager::updatePlayListItem( const soundInfoEntity &_soundInfo )
{
    if( m_currPlayListManager->findPlayItem( _soundInfo.id) )
    {
        CurrPlaySoundItem item = m_currPlayListManager->getPlayItem( _soundInfo.id );
        item.isLike = _soundInfo.is_like;
        m_currPlayListManager->updatePlayItem( item );
    }
}

void EchoMediaManager::deletePlayListItem( const QString &id )
{
    slot_mediaPlayNext();
    m_currPlayListManager->deletePlayItem( id );
}

void EchoMediaManager::playSliderValueChanged(const int _value)
{
    m_MediaPlayerManager->skipPlayPercentage( _value );
}


