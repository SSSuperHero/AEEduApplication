#ifndef ECHOFFMPEG_H
#define ECHOFFMPEG_H

#include <QThread>

class EchoFfmpeg : public QThread
{
    Q_OBJECT
public:
    explicit EchoFfmpeg(QObject *parent = 0);

    static void echoBellCut(QObject* _ffmpegOwner, const QString _soundFile, const QString _startTime,
                            const QString _endTime, const QString _outBellFile );
    void setRunFfmpegString( const QString _cutString, const QString _soundFile,
                             const QString _outBellFile, const QStringList _cutStringList );
signals:
    void signal_bellCutFinish( const QString );
public slots:

protected:
    void run();
private:
    QString         m_ffmpegFile;
    QString         m_RunFfmpegString;
    QString         m_soundFile;
    QString         m_outBellFile;

    QStringList     m_runFfmpegStringList;
};

#endif // ECHOFFMPEG_H
