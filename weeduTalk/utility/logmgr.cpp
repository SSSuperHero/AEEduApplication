#include "logmgr.h"
#include "utility/pathutil.h"
#include "config/echoconfig.h"
#include <QFile>
#include <QDateTime>
#include <QThread>
#include <QTextStream>

QString LogMgr::LogLevelToString(QtMsgType type)
{
    switch (type)
    {
        case QtDebugMsg:
            return "D";
        case QtWarningMsg:
            return "W";
        case QtCriticalMsg:
            return "E";
        case QtFatalMsg:
            return "FATAL";
        case QtInfoMsg:
            return "I";
        default:
            return "unknown";
    }
}

QString LogMgr::simplifyLogFunctionName(const QString& functionName)
{
    int pos = functionName.indexOf("(");
    if (pos != -1)
    {
        return functionName.left(pos);
    } else {
        return functionName;
    }
}

void LogMgr::customMessageHandlerImpl(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QMutexLocker mutexlock(&m_logfileMutex);

    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");

    //%{time yyyyMMdd h:mm:ss.zzz} - %{type} - %{threadid} - %{function}:%{line} - %{message}
    QString log = QString("%1 %2 - %3 - %4 - %5:%6 - %7\n").arg(QDateTime::currentMSecsSinceEpoch())
            .arg(current_date_time)
            .arg(LogLevelToString(type))
            .arg(/*QThread::currentThreadId()*/0)
            .arg(simplifyLogFunctionName(context.function))
            .arg(context.line)
            .arg(msg);

    if(pLogFile)
    {
        QTextStream txtout(pLogFile);
        txtout << endl << qUtf8Printable(log);
        txtout.flush();
    }

//    pLogFile->write(qUtf8Printable(log));
//    pLogFile->flush();

#ifdef _DEBUG
    ::OutputDebugStringW(log.toStdWString().c_str());
#endif/*_DEBUG*/
}

LogMgr::LogMgr()
{
}


QString LogMgr::getLogFileName() const
{
    return logFileName;
}

void LogMgr::changeFileName()
{

    QDateTime curDate = QDateTime::currentDateTime();
    QString today = curDate.toString("yyyy-MM-dd");

    QString fileName = "echo_" + today;
    logFileName = fileName + ".log";
//    QString actionLogFileName = fileName  + ".action.log";

    {
        QString fullFileName = PathUtil::joinPath(PathUtil::getLogDirPath(), logFileName);

        finishLogFile();
        initLogFile(fullFileName);

      }
}

bool LogMgr::initLogFile(const QString &fileName)
{
    QMutexLocker mutexlock(&m_logfileMutex);
    pLogFile = new QFile(fileName);
    if(! pLogFile->open(QIODevice::WriteOnly| QIODevice::Text|QIODevice::Append ))
    {
        return false;
    }
    return true;
}

void LogMgr::finishLogFile()
{
    QMutexLocker mutexlock(&m_logfileMutex);
    if(pLogFile && pLogFile->isOpen())
    {
        pLogFile->flush();
        pLogFile->close();
    }
    delete pLogFile;
    pLogFile = Q_NULLPTR;
}

void LogMgr::flushLog()
{
    QMutexLocker mutexlock(&m_logfileMutex);
    if(pLogFile)
    {
        pLogFile->flush();
    }
}

void LogMgr::init()
{
    QMutexLocker mutexlock(&m_initMutex);
    pLogFile = Q_NULLPTR;
    changeFileName();

    QString T_MESSAGE_PATTERN = "[%{time yyyyMMdd h:mm:ss.zzz} - %{type} - %{function}:%{line} - %{threadid}  - %{message}";
    qSetMessagePattern(T_MESSAGE_PATTERN);

//    qInstallMessageHandler(customMessageHandler);
}

LogMgr::~LogMgr()
{
    finishLogFile();
}

void LogMgr::customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    LogMgr::instance()->customMessageHandlerImpl(type, context, msg);
}
