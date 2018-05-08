#include "pathutil.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QStandardPaths>
#include <QFile>
#include <QSettings>
#include "utility/hashutility.h"

PathUtil::PathUtil()
{

}

QString PathUtil::getApplicationDirPath()
{
    return QCoreApplication::applicationDirPath();
}

QString PathUtil::getAppDataLocation()
{
    QStringList appLocations = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    if (appLocations.isEmpty())
    {
        return getApplicationDirPath();
    }

    return appLocations.at(0);
}

QString PathUtil::getImageDirPath()
{
    QString path = joinPath(getAppDataLocation(), "download/image");

    mkdir(path);

    return path;
}

QString PathUtil::getPdfDirPath()
{
    return getResourceDirPath();
}

QString PathUtil::getInstallerDirPath()
{
    QString path = joinPath(getAppDataLocation(), "download/installer");

    mkdir(path);

    return path;
}

QString PathUtil::getResourceConfigFilePath()
{
    QString filename = PathUtil::getAppDataLocation() + QString("/resourceConfig.ini");

    return filename;
}

QString PathUtil::getLanguagesXmlFilePath()
{
    QString filename =QCoreApplication::applicationDirPath()+ QString("/language/languagesdoc.xml");

    return filename;
}

QString PathUtil::getResourceDirPath()
{
    QString path = joinPath(getAppDataLocation(), "download/resource");
    mkdir(path);

    return path;
}

QString PathUtil::getBellDirPath()
{
    QString path = joinPath(getAppDataLocation(), "download/bell");
    mkdir(path);

    return path;
}

QString PathUtil::getBellFileName( const QString _fileName )
{
    QString path = getBellDirPath();
    path += "/" + HashUtility::toMd5(_fileName) + ".m4a";

    return path;
}

QString PathUtil::getResourceDirPath(QString /*mid*/)
{
    //some consuctive classes use same video && audio resources
   // QString path = joinPath(getResourceDirPath(), mid);

    QString path = getResourceDirPath();

    mkdir(path);

    return path;
}

QString PathUtil::getLogDirPath()
{
    //should put into %appdata% dir getApplicationDirPath
//    QString path = joinPath(getAppDataLocation(), "log");
    QString path = joinPath(getApplicationDirPath(), "log");

    mkdir(path);

    return path;
}

QString PathUtil::getDumpDirPath()
{
    return getLogDirPath();
}

QString PathUtil::getCutImageDirPath()
{
    QString cutImagePath = joinPath(getAppDataLocation(), "cutImage");

    mkdir(cutImagePath);

    return cutImagePath;
}


QString PathUtil::getConfigDirPath()
{
    QString ConfigPath = joinPath(getAppDataLocation(), "config");
    mkdir(ConfigPath);

    return ConfigPath;
}

QString PathUtil::getDeviceConfigFilePath()
{
    QString filename = PathUtil::getConfigDirPath() + QString("/newDeviceConfig.ini");

    return filename;
}

QString PathUtil::getTeacherAudioResourceDirPath(const QString &mid)
{
    return getResourceDirPath(mid);
}

QString PathUtil::getTeacherVideoResourceDirPath(const QString &mid)
{
    return getResourceDirPath(mid);
}

QString PathUtil::getMusicCatchPath()
{
    QString path = joinPath(getAppDataLocation(), "musicCatch");

    mkdir(path);

    QString filename = path + QString("/catch.dat");

    return filename;
}

void PathUtil::mkdir(const QString &dirPath)
{
//    qInfo("dirPath:%s", qUtf8Printable(dirPath));

    //it might not a good idea to put create dir here
    if (!QFile::exists(dirPath))
    {
//        qWarning("path:%s not exists, create it", qUtf8Printable(dirPath));
        if (!QDir::root().mkpath(dirPath))
        {
//            qCritical("mkpath:%s failed", qUtf8Printable(dirPath));
        }
    }
}

void PathUtil::remove(const QString &fileName)
{
    if(QFile::exists(fileName))
    {
        QFile::remove(fileName);
    }
}

QString PathUtil::joinPath(const QString &dirPath, const QString &fileName)
{
    QFileInfo fi(QDir(dirPath), fileName);

    return fi.absoluteFilePath();
}
