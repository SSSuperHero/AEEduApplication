#include "NetWorkDownloadReplyHolder.h"

#include <QTimer>
#include <QApplication>
#include <QDir>
#include <QUuid>
#include <utility/hashutility.h>
//#include <utility/pathutil.h>

static QEvent::Type EVENT_TYPE_ON_START =  static_cast<QEvent::Type>(QEvent::User + 1);
static QEvent::Type EVENT_TYPE_ON_ALREADY_EXISTS =  static_cast<QEvent::Type>(QEvent::User + 2);
static QEvent::Type EVENT_TYPE_ON_ABORT =  static_cast<QEvent::Type>(QEvent::User + 3);

static const QString KEY_TEMP = ".echo";

NetWorkDownloadReplyHolder::NetWorkDownloadReplyHolder(QObject* owner, const QString& url_, const QString& dirPath_, const bool _resetName, QNetworkReply* reply_)
    : QObject(owner)
    , url(url_)
    , dirPath(dirPath_)
    , reply(reply_)
    , isError(false)
    , shouldAbort(false)
    , onStartEmitted(false)
    , m_isResetName(_resetName)
{
    //can event be deleted automatically?
    qInfo("this:%x, ctor url:%s, dirPath:%s", this, qUtf8Printable(url_), qUtf8Printable(dirPath_));

    QApplication::postEvent(this, new QEvent(EVENT_TYPE_ON_START));

    if (reply != NULL)
    {
//        qDebug("this:%x,connect reply signals", this);
        connect(reply, &QIODevice::readyRead, this, &NetWorkDownloadReplyHolder::slot_readyRead);
        connect(reply, &QNetworkReply::finished, this, &NetWorkDownloadReplyHolder::slot_finished);
        connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &NetWorkDownloadReplyHolder::slot_error);
        connect(reply, &QNetworkReply::downloadProgress, this, &NetWorkDownloadReplyHolder::slot_downloadProgress);
    }

    initDownloadFile();
}

void NetWorkDownloadReplyHolder::initDownloadFile()
{
//    qInfo("this:%x, initDownloadFile", this);

    QString fileName = generateFileName(url);
//    qInfo("this:%x,generateFileName:%s", this, qUtf8Printable(fileName));

    if( m_isResetName )
    {
        filePath = QDir(dirPath).filePath(fileName);
        qInfo("this:%x,download file path:%s", this, qUtf8Printable(filePath));
        if (QFile::exists(filePath))
        {
            qInfo("this:%x,file already exists", this);

            QApplication::postEvent(this, new QEvent(EVENT_TYPE_ON_ALREADY_EXISTS));
            return;
        }
        filePath = generateTempFilePath();
    }
    else
    {
        filePath = dirPath;
    }

    downloadFile.setFileName(filePath);
    if (!downloadFile.open(QIODevice::WriteOnly))
    {
        //need to emit failed signal
        qCritical("this:%x,open download file failed:%s", this, qUtf8Printable(downloadFile.errorString()));
        return;
    }
}

QString NetWorkDownloadReplyHolder::generateFileName(const QString& urlString)
{
    QUrl url(urlString);
    QString fileName = url.fileName();
    QString fileExtension = QFileInfo(fileName).suffix();
//    qInfo("generateFileName, url:%s, fileName:%s, fileExtension:%s",
//          qUtf8Printable(urlString),
//          qUtf8Printable(fileName),
//          qUtf8Printable(fileExtension));

    if (!fileExtension.isEmpty())
    {
        return HashUtility::toMd5(urlString) + "." + fileExtension;
    } else
    {
        return HashUtility::toMd5(urlString);
    }
}

bool NetWorkDownloadReplyHolder::isFileAlreadyDownloaded(const QString &url, const QString& dirPath)
{
    QString filePath = getDownloadedFilePath(url, dirPath);
//    qInfo("download file path:%s", qUtf8Printable(filePath));

    return QFile::exists(filePath);
}

QString NetWorkDownloadReplyHolder::getDownloadedFilePath(const QString &url, const QString &dirPath)
{
    QString fileName = generateFileName(url);
//    qInfo("isFileAlreadyDownloadedgenerateFileName:%s", qUtf8Printable(fileName));

    return QDir(dirPath).filePath(fileName);
}

void NetWorkDownloadReplyHolder::abort()
{
    qInfo("this:%x,abort", this);
    shouldAbort = true;

    if (reply)
    {
//        qInfo("this:%x, before real abort", this);

        reply->abort();

        qInfo("this:%x,after real abort, network reply:QNetworkReply dies", this);
        reply = NULL;

        QApplication::postEvent(this, new QEvent(EVENT_TYPE_ON_ABORT));
    }
}
QString NetWorkDownloadReplyHolder::generateTempFilePath()
{
    QString uuid = QUuid::createUuid().toString();

    return filePath + KEY_TEMP + uuid;
}

NetWorkDownloadReplyHolder::~NetWorkDownloadReplyHolder()
{
    qInfo("this:%x,network reply:NetWorkDownloadReplyHolder dies", this);


    if (reply)
    {
//        reply->abort();

        qInfo("this:%x,network reply:QNetworkReply dies", this);
        delete reply;
    }
}

void NetWorkDownloadReplyHolder::customEvent(QEvent *event)
{
    if (!event)
    {
        return;
    }

    QEvent::Type type = event->type();
    if (type == EVENT_TYPE_ON_START)
    {
        qInfo("this:%x,recv EVENT_TYPE_ON_START", this);

        if (shouldAbort)
        {
            qInfo("this:%x,shouldAbort is true, no need to emit signal", this);
            return;
        }

       emitOnStartSignal();

    } else if (type == EVENT_TYPE_ON_ALREADY_EXISTS)
    {
        qInfo("this:%x,recv EVENT_TYPE_ON_ALREADY_EXISTS", this);

        qInfo("this:%x,emit signal_onSuccess url:%s", this, qUtf8Printable(url));

        closeFile();

        if (shouldAbort)
        {
            qInfo("this:%x,shouldAbort is true, no need to emit signal", this);
            return;
        }

        emit signal_onSuccess(filePath);

        qInfo("this:%x,emit signal_onFinish url:%s", this, qUtf8Printable(url));
        emit signal_onFinish();
    }
    else if (type == EVENT_TYPE_ON_ABORT)
    {
        emit signal_abort();
    }
}

void NetWorkDownloadReplyHolder::onFinished()
{
    qInfo("this:%x,onFinished", this);

    closeFile();
//    qInfo("deleteLater");
//    this->deleteLater();

    if (shouldAbort)
    {
        qInfo("this:%x,shouldAbort is true, no need to emit signal", this);
        return;
    }

    qInfo("this:%x,signal_onFinish, url:%s", this, qUtf8Printable(url));

    emit signal_onFinish();
}

void NetWorkDownloadReplyHolder::closeFile()
{
    qInfo("this:%x,closeFile", this);
    if (downloadFile.isOpen())
    {
        downloadFile.flush();

        qInfo("this:%x,close downloadfile", this);
        downloadFile.close();
    }
}

void NetWorkDownloadReplyHolder::emitOnStartSignal()
{
    qInfo("emitOnStartSignal");

    emit signal_onStart();

    onStartEmitted = true;
}

void NetWorkDownloadReplyHolder::slot_readyRead()
{
    QByteArray byteArray = reply->readAll();
    downloadFile.write(byteArray);
    downloadFile.flush();
}

void NetWorkDownloadReplyHolder::slot_finished()
{
    qInfo("this:%x,slot_finished", this);
    if (isError)
    {
        qInfo("this:%x,already handled in error", this);
        return;
    }

    filePath = mvTempFileFinal();

    QFile _tFile(filePath);

    qInfo()<<"slot_finished filePath:"<< filePath;
//    if (filePath.isEmpty())
    if ( !_tFile.exists() )
    {
        qCritical("this:%x,mvTempFileFinal failed", this);

        if (shouldAbort)
        {
            qInfo("this:%x,shouldAbort is true, no need to emit signal", this);
            return;
        }

        emit signal_onFailure(DOWNLOAD_ERR_MV_FAILED);
    }
    else
    {
        //response might not string
        qInfo("this:%x,signal_onSuccess, url:%s", this, qUtf8Printable(url));

        if (shouldAbort)
        {
            qInfo("this:%x,shouldAbort is true, no need to emit signal", this);
            return;
        }

        emit signal_onSuccess(filePath);
    }

    onFinished();
}

QString NetWorkDownloadReplyHolder::mvTempFileFinal()
{
    qInfo("this:%x,mvTempFileOfficial", this);
    int p = filePath.indexOf(KEY_TEMP);
    if (p == -1)
    {
        qCritical("error");
        return "";
    }

    QString finalFilePath = filePath.left(p);
    qInfo("this:%x,final finalFilePath:%s", this, qUtf8Printable(finalFilePath));

    closeFile();
    bool ret = QFile::rename(filePath, finalFilePath);
//    return ret ? finalFilePath : "";
    return finalFilePath;
}

void NetWorkDownloadReplyHolder::slot_error(QNetworkReply::NetworkError code)
{
    qCritical("this:%x,slot_error, code:%d", this, code);
    isError = true;

    // delete download error's file.[add by Spencer]
    if(downloadFile.isOpen())
    {
        downloadFile.close();
        downloadFile.remove();
    }

    //use minus error code to identity low level error(not protocol level error)
    int errorCode = -(int)code;

    if (shouldAbort)
    {
        qInfo("this:%x,shouldAbort is true, no need to emit signal", this);
        return;
    }

    if (!onStartEmitted)
    {
       //拔网线的时候，slot_error可能先emit,然后才轮到onStart
       emitOnStartSignal();
    }


    qInfo("this:%x,signal_onFailure, url:%s", this, qUtf8Printable(url));
    emit signal_onFailure(errorCode);

    onFinished();
}

void NetWorkDownloadReplyHolder::slot_downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
//    qDebug("this:%x,slot_downloadProgress bytesReceived:%lld, bytesTotal:%lld", this, bytesReceived, bytesTotal);

    //why bytesTotal is -1?
    if (bytesTotal == -1)
    {
        qWarning("this:%x,bytesTotal is -1", this);
        return;
    }

    double percent = ((double)bytesReceived / (double)bytesTotal) * 100;
//    qDebug(qUtf8Printable(QString("download percent:%1").arg(percent)));

    if (shouldAbort)
    {
        qInfo("this:%x,shouldAbort is true, no need to emit signal", this);
        return;
    }

    emit signal_downloadProgress(percent, bytesReceived, bytesTotal);
}


