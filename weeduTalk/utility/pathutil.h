#ifndef PATHUTIL_H
#define PATHUTIL_H

#include <QString>



class PathUtil
{
public:
    PathUtil();
    static QString getApplicationDirPath();
    static QString getAppDataLocation();
    static QString getImageDirPath();
    static QString getPdfDirPath();
    static QString getInstallerDirPath();
    static QString getLogDirPath();
    static QString getDumpDirPath();
    static QString getCutImageDirPath();
    static QString getConfigDirPath();
    static QString getTeacherAudioResourceDirPath(const QString& mid);
    static QString getTeacherVideoResourceDirPath(const QString& mid);
    static QString getMusicCatchPath();

    static void    mkdir(const QString& dirPath);
    static void    remove(const QString& fileName);
    static QString joinPath(const QString& dirPath, const QString& fileName);
    static QString getResourceDirPath();
    static QString getResourceDirPath(QString mid);

    static QString getDeviceConfigFilePath();
    static QString getResourceConfigFilePath();
    static QString getLanguagesXmlFilePath();
    static QString getBellDirPath();
    static QString getBellFileName( const QString _fileName );
};

#endif // PATHUTIL_H
