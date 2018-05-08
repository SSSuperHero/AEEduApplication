#include "echocurrplaylistmanager.h"
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QByteArray>
#include <QList>
#include <QTime>
#include "utility/pathutil.h"

//#define             CATCH_PATH_CURR_PLAY_LIST       "./catch.dat"

EchoCurrPlayListManager::EchoCurrPlayListManager(QObject *parent) :
    QObject(parent),
    m_currentPlayId("")
{
    read_catch_data();
}

void EchoCurrPlayListManager::read_catch_data()
{
    m_currentPlayMap.clear();
    m_currentPlayList.clear();
    QFile fp( PathUtil::getMusicCatchPath() );
    if(fp.open(QIODevice::ReadOnly))
    {
        QByteArray bt = fp.readAll();
        QJsonObject json_object = QJsonDocument::fromJson(bt).object();
        parse_json(json_object);
    }
    fp.close();
}
void EchoCurrPlayListManager::write_catch_data()
{
    QJsonArray arr;
//    QHashIterator<QString, CurrPlaySoundItem> i(m_currentPlayMap);

    foreach ( QString _id, m_currentPlayList )
    {
//        CurrPlaySoundItem _item = m_currentPlayMap.find( _id );
        CurrPlaySoundItem _item = getPlayItem( _id );
        QJsonObject obj;
        obj.insert("id",_item.id);
        obj.insert("name",_item.name);
        obj.insert("like",_item.isLike);
        obj.insert("len",_item.len);
        arr.append(obj);
    }
//    while ( i.hasNext() )
//    {
//        i.next();
//        CurrPlaySoundItem _item=i.value();
//        QJsonObject obj;
//        obj.insert("id",_item.id);
//        obj.insert("name",_item.name);
//        obj.insert("like",_item.isLike);
//        obj.insert("len",_item.len);
//        arr.append(obj);
//    }
    QJsonObject obj;
    obj.insert("arr",arr);
    QByteArray bt = QJsonDocument(obj).toJson();
    remove( PathUtil::getMusicCatchPath().toLatin1().data() );
    QFile fp( PathUtil::getMusicCatchPath() );
    if( fp.open(QIODevice::WriteOnly) )
    {
        fp.write(bt);
    }
    fp.close();
}

void EchoCurrPlayListManager::parse_json(const QJsonObject& obj)
{
    if(!obj.isEmpty())
    {
        if(obj.contains("arr"))
        {
            m_currentPlayList.clear();
            m_currentPlayMap.clear();

            QJsonArray arr=obj.value("arr").toArray();
            for( int i = 0;i < arr.size(); i++ )
            {
                QJsonObject _value=arr.at(i).toObject();
                CurrPlaySoundItem item;
                if(_value.contains("id"))
                {
                    item.id=_value.value("id").toString();
                }
                if(_value.contains("name"))
                {
                    item.name=_value.value("name").toString();
                }
                if(_value.contains("like"))
                {
                    item.isLike=_value.value("like").toInt();
                }
                if(_value.contains("len"))
                {
                    item.len=_value.value("len").toString();
                }
                m_currentPlayList.append( item.id );
                m_currentPlayMap.insert( item.id, item );
            }
        }
    }
}
void EchoCurrPlayListManager::insertPlayItem( const CurrPlaySoundItem& item, const QString _insertId )
{
    m_lock.lock();

    if( _insertId.toInt() > 0 )
        m_currentPlayList.insert( m_currentPlayList.indexOf( _insertId ) + 1, item.id );
    else
        m_currentPlayList.append( item.id );

    m_currentPlayMap.insert( item.id, item );
    m_lock.unlock();

    write_catch_data();
}

void EchoCurrPlayListManager::deletePlayItem( const QString &id )
{
    m_lock.lock();
    QHash<QString, CurrPlaySoundItem>::iterator i = m_currentPlayMap.find(id);
    while (i != m_currentPlayMap.end() && i.key() == id)
    {
        i = m_currentPlayMap.erase(i);
        m_currentPlayList.removeOne( id );
    }
    m_lock.unlock();

    write_catch_data();
}

bool EchoCurrPlayListManager::findPlayItem( QString id )
{
    QHash<QString, CurrPlaySoundItem>::iterator i = m_currentPlayMap.find(id);
    while (i != m_currentPlayMap.end() && i.key() == id)
    {
        return true;
    }
    return false;
}

CurrPlaySoundItem EchoCurrPlayListManager::getPlayItem(QString id)
{
    CurrPlaySoundItem item;
    QHash<QString, CurrPlaySoundItem>::iterator i = m_currentPlayMap.find(id);
    while (i != m_currentPlayMap.end() && i.key() == id)
    {
        item=i.value();
        break;
    }
    return item;
}

CurrPlaySoundItem EchoCurrPlayListManager::getCurrrentPlayItem()
{
    CurrPlaySoundItem item;
    QHash<QString, CurrPlaySoundItem>::iterator i = m_currentPlayMap.find(m_currentPlayId);
    while (i != m_currentPlayMap.end() && i.key() == m_currentPlayId)
    {
        item = i.value();
        break;
    }
    return item;
}

void EchoCurrPlayListManager::updatePlayItem(const CurrPlaySoundItem& item)
{
    QHash<QString, CurrPlaySoundItem>::iterator i = m_currentPlayMap.find(item.id);
    while (i != m_currentPlayMap.end() && i.key() == item.id)
    {
        i = m_currentPlayMap.erase(i);
        m_currentPlayList.removeOne( item.id );
    }

    insertPlayItem(item);

//    write_catch_data();
}

void EchoCurrPlayListManager::clear_data()
{
    m_currentPlayMap.clear();
    m_currentPlayList.clear();

    emit signal_playListClear();

    write_catch_data();
}

void EchoCurrPlayListManager::getLastPlayItem(QString& id)
{
    QList<QString> _list = m_currentPlayList;//m_currentPlayMap.keys();
    if(_list.length() <= 0)
        return;

    if( getCurrentPlayId().toInt() <= 0 || _list.length() == 1 )
    {
        id = _list.at(0);
        return;
    }

    int nCount = 0;
    QString temp = getCurrentPlayId();

    for(int i = 0;i < _list.length();i++)
    {
        if(_list.at(i) == temp)
        {
            nCount = i;
            break;
        }
    }

    if(nCount > 0)
        nCount -= 1;
    else
        nCount = _list.length() -1 ;

    id = _list.at(nCount);
}

void EchoCurrPlayListManager::getNextPlayItem( QString& id )
{
    QList<QString> _list = m_currentPlayList;//m_currentPlayMap.keys();
    if( _list.length() <= 0 )
        return;

    if( getCurrentPlayId().toInt() <= 0 || _list.length() == 1 )
    {
        id = _list.at(0);
        return;
    }

    int nCount = 0;

    QString tempId = getCurrentPlayId();
    for(int i = 0;i < _list.length();i++)
    {
        if( _list.at( i ) == tempId )
        {
            nCount = i;
            break;
        }
    }

    if( nCount == _list.length() - 1 )
        nCount = 0;
    else
        nCount += 1;

    id = _list.at(nCount);
}

void EchoCurrPlayListManager::getRandomPlayItem(QString& id)
{
    QList<QString> _list = m_currentPlayList;//m_currentPlayMap.keys();
    if( _list.length() <= 0 )
        return;

    if( getCurrentPlayId().toInt() <= 0 || _list.length() == 1 )
    {
        id=_list.at(0);
        return;
    }

    qsrand( QTime(0,0,0).secsTo(QTime::currentTime()) );
    int nCount = _list.length() - 1;
    int temp = qrand()%nCount;
    id = _list.at(temp);
}

CurrPlaySoundItem EchoCurrPlayListManager::getFristPlayItem()
{
    CurrPlaySoundItem item;
    QHash<QString, CurrPlaySoundItem>::iterator it = m_currentPlayMap.begin();
    if(it!=m_currentPlayMap.end())
    {
        item=it.value();
    }

    return item;
}

QHash<QString, CurrPlaySoundItem> EchoCurrPlayListManager::getCurrentPlayMap()
{
    return m_currentPlayMap;
}

QStringList EchoCurrPlayListManager::getCurrentPlayList()
{
    return m_currentPlayList;
}

void EchoCurrPlayListManager::setCurrentPlayId( const int &_playId )
{
    m_currentPlayId = QString::number( _playId );
}

QString EchoCurrPlayListManager::getCurrentPlayId()
{
    QString _id = "0";
    QList<QString> _list = m_currentPlayMap.keys();
    if( _list.length() <= 0 )
        return "0";

    if( m_currentPlayId <= 0 || _list.length() == 1 )
    {
        _id = _list.at(0);

        return _id;
    }

//    qDebug()<<"getCurrentPlayId _id:" << m_currentPlayId;
    return m_currentPlayId;
}
