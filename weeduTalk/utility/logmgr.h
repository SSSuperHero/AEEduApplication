#ifndef LOGMGR_H
#define LOGMGR_H

#include <utility/singletonmgrbase.h>
#include <QFile>
#include <mutex>
#include <QMutex>

class LogMgr: public SingletonMgrBase
{
    Q_OBJECT

#ifdef Q_OS_MAC
    MY_DECLARE_SINGLETON(LogMgr)
#else
    DECLARE_SINGLETON(LogMgr)
    // SingletonMgrBase interface
#endif

public:
    LogMgr();
    void init();
    ~LogMgr();

    QString getLogFileName() const;
    void changeFileName();
    bool initLogFile(const QString& fileName);
    void finishLogFile();
    void flushLog();

private:
    static void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    void customMessageHandlerImpl(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    QString simplifyLogFunctionName(const QString& functionName);
    QString LogLevelToString(QtMsgType type);

private:
    QString         logFileName;
    QFile*          pLogFile;
    QMutex          m_logfileMutex;
    QMutex          m_initMutex;

};

#endif // LOGMGR_H
