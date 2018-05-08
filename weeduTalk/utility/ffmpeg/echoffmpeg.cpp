#include "echoffmpeg.h"
#include <QProcess>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include "utility/widget/mesgboxwidhget.h"
#include "widget/assistWidget/echobellmodule.h"

EchoFfmpeg::EchoFfmpeg(QObject *parent) :
    QThread(parent)
{
    m_ffmpegFile = QCoreApplication::applicationDirPath() + "/ffmpeg";
}

void EchoFfmpeg::run()
{
    QFile::remove(m_outBellFile);

    qDebug()<<"echoffmpeg RunFfmpegString:"<<m_RunFfmpegString;
//    int _code = QProcess::execute( m_RunFfmpegString, QStringList() );
    int _code = QProcess::execute( m_ffmpegFile, m_runFfmpegStringList );
    qDebug()<<"echoffmpeg _code:"<<_code;

    if( _code == 0 )
    {
        emit signal_bellCutFinish( m_outBellFile );
    }
}

void EchoFfmpeg::setRunFfmpegString( const QString _cutString, const QString _soundFile,
                                     const QString _outBellFile, const QStringList _cutStringList )
{
    m_RunFfmpegString = m_ffmpegFile + _cutString;
    m_soundFile = _soundFile;
    m_outBellFile = _outBellFile;

    m_runFfmpegStringList = _cutStringList;
}

void EchoFfmpeg::echoBellCut( QObject* _ffmpegOwner, const QString _soundFile, const QString _startTime,
                  const QString _LenTime, const QString _outBellFile )
{
    QString _cutString = QString(" -ss %1 -t %2 -i %3 %4").arg(_startTime).arg(_LenTime)
            .arg(_soundFile).arg(_outBellFile);

    QStringList _cutStringList;
    _cutStringList.append("-ss");
    _cutStringList.append(_startTime);
    _cutStringList.append("-t");
    _cutStringList.append(_LenTime);
    _cutStringList.append("-i");
    _cutStringList.append(_soundFile);
    _cutStringList.append(_outBellFile);

    EchoFfmpeg *_echoFfmpeg = new EchoFfmpeg( _ffmpegOwner );
    _echoFfmpeg->setRunFfmpegString( _cutString, _soundFile, _outBellFile, _cutStringList );
    connect( _echoFfmpeg, &EchoFfmpeg::signal_bellCutFinish,
             (EchoBellModule*)_ffmpegOwner, &EchoBellModule::slot_bellCutFinish);
    connect(_echoFfmpeg, SIGNAL(finished()), _echoFfmpeg, SLOT(deleteLater()));
    _echoFfmpeg->start();
}
