#ifndef ECHOUPLOADBELL_H
#define ECHOUPLOADBELL_H

#include <QThread>
#include <mgr/http/networkimagereplyholder.h>

class EchoUploadBell : public QThread
{
    Q_OBJECT

    void getQiniuToken();
public:
    EchoUploadBell(QObject *parent = 0);
    void setUplodeInfo(const QString _key, const QString _localFile, const QString _token);

    static void uplodeQiniu(QObject *_uplodeOwner, const QString _key,
                            const QString _localFile, const QString _token);

public:
signals:
    void signal_uploadBellFinish( const QString _key );

protected:
    void run();

    QString     m_uploadKey;
    QString     m_uploadFile;
    QString     m_uploadToken;
};

#endif // ECHOUPLOADBELL_H
