#ifndef ECHOPARSEWEBMEDIA_H
#define ECHOPARSEWEBMEDIA_H

#include <QObject>
#include <QQueue>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include "config/define.h"
#include "mgr/http/module/echohttpinfoentity.h"


enum WEB_CMD_TYPE
{
    CMD_HIDE_REGISTER_WIDGET = 0,
    CMD_SOUND_PLAY_DO,
    CMD_BELL_PLAY_DO,
    CMD_BELL_LOG_PLAY_DO,
    CMD_STATUS_MV_PLAY,
    CMD_SOUND_PLAY_LIST,
    CMD_PLAY_NEXT_SOUND,
    CMD_ADD_SOUND_TO_CUR_LIST,
    CMD_LAUSE_PALUE_PLAY,
    CMD_MAIN_WEB_MINI,
    CMD_MAIN_WEB_MAX,
    CMD_MAIN_WEB_INIT,
    CMD_USER_REG_AFTER,
    CMD_SYS_BROWER_OPEN,
    CMD_BELL_MAKE_SAVE,
    CMD_BELL_DOWNLOAD_DO,
    CMD_BELL_DOWNLOAD_LOG_DO,
    CMD_OPEN_EXTERNAL_BROWSER,
    STATUES_PAGE_CHANGE
};

class ThreasWork : public QThread
{
    Q_OBJECT
public:

    class QueueData
    {
    public:
        QueueData(){}
    public:
        QString m_name;
        QJsonObject m_param;
    };

    ThreasWork()
    {
        m_run = true;
    }
signals:
    void sendThreadData( QString name ,QJsonObject param );
public:
    void run();

    void addQueue(const QString &_name,const QJsonObject &_param);

    void start_work();

private:
    QMutex m_lock;
    QQueue<QueueData> m_queue;
    QWaitCondition m_waite;
    bool m_run;
};

class EchoParseWebMedia : public QObject
{
    Q_OBJECT

public:
    explicit EchoParseWebMedia(QObject *parent = 0);

    void addWebMediaMsg(const QString &_name, const QJsonObject &_param);
    void do_cmd();
private:
    void initMap();

    void webViewWidgetClose(QJsonObject);
    void sound_play_do(QJsonObject param);
    void bell_play_do(QJsonObject param);
    void status_mv_play(QJsonObject);
    void sound_play_list(QJsonObject param);
    void play_next_sound(QJsonObject param);
    void add_sound_to_cur_list(QJsonObject param);
    void pause_palue_play(QJsonObject param);
    void main_web_mini(QJsonObject);
    void statues_page_change(QJsonObject param);
    void user_reg_after(QJsonObject param);
    void sys_brower_open(QJsonObject param);
    void beel_make_save(QJsonObject param);
    void bell_download_log_do(QJsonObject param);
    void bell_download_do(QJsonObject param);  
    void bell_log_play_do(QJsonObject param);
    void openExternalBrowser(QJsonObject param);

    void mainWebShowtype(const WIDGET_SHOW_TYPE);

signals:
    void signal_soundPlayListDo( QJsonArray _soundArr );
    void signal_soundNextPlayDo( int soundId );
    void signal_bellPlayDo( int soundId );
    void signal_bellLogPlayDo( int soundId );
    void signal_soundPlayDo( int soundId, bool _remind );
    void signal_soundPauseDo( int soundId );
    void signal_soundAddPlayList( int soundId );
    void signal_webWidgetClose();
    void signal_webPageChange( const WEB_PAGE_TYPE _webPage );
    void signal_videoPlayDo();
    void signal_changeWidgetShowType( const WIDGET_SHOW_TYPE );
    void signal_userRegAfter( const QString, const QString );
    void signal_sysBrowerOpen( const QString );
    void signal_bellMakeSave( const echoBellEditInfo );
    void signal_BellDownloadDo( int soundId );
    void signal_BellDownloadLogDo( int soundId );

    void signal_webMusicInfoMin( bool );
public slots:
    void ParseWebMsg(QString _name, QJsonObject _param);
private:
    QMap<QString,WEB_CMD_TYPE>    g_webReplyMap;

    QMap<QString,WEB_PAGE_TYPE>  g_webPageMap;

    ThreasWork                    *m_threadWork;
};

#endif // ECHOPARSEWEBMEDIA_H
