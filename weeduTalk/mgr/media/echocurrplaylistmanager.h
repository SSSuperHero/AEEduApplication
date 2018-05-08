#ifndef ECHOCURRPLAYLISTMANAGER_H
#define ECHOCURRPLAYLISTMANAGER_H

#include <QObject>
#include <QHash>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QMutex>


class CurrPlaySoundItem
{
public:
    QString id;
    QString name;
    int isLike;
    QString len;
};


class EchoCurrPlayListManager : public QObject
{
    Q_OBJECT
public:
    explicit EchoCurrPlayListManager(QObject *parent = 0);

public:
    void insertPlayItem(const CurrPlaySoundItem&, const QString _insertId = 0 );
    void deletePlayItem( const QString &id );
    void updatePlayItem(const CurrPlaySoundItem&);
    bool findPlayItem(QString);
    CurrPlaySoundItem getPlayItem(QString);
    CurrPlaySoundItem getCurrrentPlayItem();
    void write_catch_data();
    void clear_data();
    void getLastPlayItem(QString& id);
    void getNextPlayItem(QString& id);
    void getRandomPlayItem(QString& id);
    CurrPlaySoundItem getFristPlayItem();

    void setCurrentPlayId( const int &_playId );
    QString getCurrentPlayId();

    QStringList getCurrentPlayList();
    QHash<QString, CurrPlaySoundItem> getCurrentPlayMap();

public:
signals:
    void signal_playListClear();

private:
    void read_catch_data();
    void parse_json(const QJsonObject&);
private:
    QHash<QString,CurrPlaySoundItem> m_currentPlayMap;
    QStringList m_currentPlayList;

    QMutex m_lock;

    QString            m_currentPlayId;
};

#endif // ECHOCURRPLAYLISTMANAGER_H
