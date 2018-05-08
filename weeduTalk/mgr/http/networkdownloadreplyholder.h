#ifndef NetWorkDownloadReplyHolder_H
#define NetWorkDownloadReplyHolder_H

#include <QEvent>
#include <QNetworkReply>
#include <QByteArray>
#include <QFile>

#define DOWNLOAD_ERR_MV_FAILED -999

class NetWorkDownloadReplyHolder: public QObject
{
    Q_OBJECT
public:
    NetWorkDownloadReplyHolder(QObject* owner, const QString& url, const QString& dirPath,
                               const bool _resetName, QNetworkReply* reply_);

    ~NetWorkDownloadReplyHolder();

    void initDownloadFile();
    static QString generateFileName(const QString& url);
    static bool isFileAlreadyDownloaded(const QString& url, const QString& dirPath);
    static QString getDownloadedFilePath(const QString& url, const QString& dirPath);
    void abort();

    QString mvTempFileFinal();

private:
    QString generateTempFilePath();

signals:
    void signal_onStart();
    void signal_onFinish();
    void signal_onSuccess(const QString& filePath);
    void signal_onFailure(int errorCode);
    void signal_downloadProgress(double percent, qint64 bytesReceived, qint64 bytesTotal);
    void signal_abort();

private slots:
    void slot_readyRead();
    void slot_finished();
    void slot_error(QNetworkReply::NetworkError code);
    void slot_downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    // QObject interface
private:
    void customEvent(QEvent *event);
    void onFinished();
    void closeFile();
    void emitOnStartSignal();

private:
    QString        url;
    QString        dirPath;
    QNetworkReply* reply;
    bool           isError;
    QFile          downloadFile;
    QString        filePath;
    bool           shouldAbort;
    bool           onStartEmitted;

    bool           m_isResetName;
};

#endif // NetWorkDownloadReplyHolder_H
