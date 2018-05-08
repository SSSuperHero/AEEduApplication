#include "hashutility.h"
#include <QCryptographicHash>
#include <QFile>

HashUtility::HashUtility()
{

}

QString HashUtility::toMd5(const QString& message)
{
    return QCryptographicHash::hash(message.toLocal8Bit(),QCryptographicHash::Md5).toHex();

}

QString HashUtility::fileToMd5(const QString &filePath)
{
    if (!QFile::exists(filePath))
    {
        qCritical("no such filepath:%s", qUtf8Printable(filePath));
        return "";
    }

    QFile f(filePath);
     if (!f.open(QFile::ReadOnly))
     {
         qCritical("f.open failed");
         return "";
     }

     QCryptographicHash hash(QCryptographicHash::Md5);
     if (!hash.addData(&f))
     {
         qCritical("addData failed");
         return "";
     }

     return hash.result().toHex();
}
