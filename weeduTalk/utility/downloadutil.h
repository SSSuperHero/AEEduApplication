#ifndef DOWNLOADUTIL_H
#define DOWNLOADUTIL_H

#include <mgr/http/NetWorkDownloadReplyHolder.h>
#include <mgr/http/networkimagereplyholder.h>

class DownloadUtil
{
public:
    DownloadUtil();
    static NetWorkDownloadReplyHolder* downloadImage(QObject* owner, const QString& url);
    static NetworkImageReplyHolder* downloadImage(QObject* owner, const QString& url, QWidget* label,
                                                  const QString& styleSheetSectionName,
                                                  bool bBackgroundImage = true,
                                                  const QString& failedImagePath = "",
                                                  const QString& initImagePath = "");

    static QString getDownloadedImageFilePath(const QString& url);
    static NetWorkDownloadReplyHolder *downloadInstaller(QObject *owner, const QString &url);
    static NetWorkDownloadReplyHolder *downloadSound(QObject *owner, const QString &url, const QString &_fileName);
};

#endif // DOWNLOADUTIL_H
