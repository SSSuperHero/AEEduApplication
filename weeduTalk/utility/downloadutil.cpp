#include "downloadutil.h"
#include "pathutil.h"
#include "mgr/http/httpmgr.h"
#include "utility/widget/imageutil.h"

DownloadUtil::DownloadUtil()
{

}

NetWorkDownloadReplyHolder *DownloadUtil::downloadImage(QObject* owner, const QString &url)
{
    qInfo("downloadImage url:%s", qUtf8Printable(url));
    return HttpMgr::instance()->download(owner, url, PathUtil::getImageDirPath());
}

NetworkImageReplyHolder *DownloadUtil::downloadImage(QObject *owner, const QString &url, QWidget *label,
                                                     const QString& styleSheetSectionName, bool bBackgroundImage,
                                                     const QString &failedImagePath, const QString &initImagePath)
{
     qInfo("NetworkImageReplyHolder downloadImage url:%s", qUtf8Printable(url));

     if (!url.toLower().startsWith("http"))
     {
         qInfo("it's a local file");
         ImageUtil::setBackgroundImage(label, styleSheetSectionName, url, bBackgroundImage);
         return NULL;
     }

     //owner should be network iamge reply holder?
     NetWorkDownloadReplyHolder* reply = HttpMgr::instance()->download(owner, url, PathUtil::getImageDirPath());

     NetworkImageReplyBuilder builder;
     builder.setWidget(label).setInitImagePath(initImagePath).setFailedImagePath(failedImagePath).
             setStyleSheetSectionName(styleSheetSectionName).setIsBackgroundImage(bBackgroundImage);
     return new NetworkImageReplyHolder(owner, reply, builder);
}

QString DownloadUtil::getDownloadedImageFilePath(const QString &url)
{
    return NetWorkDownloadReplyHolder::getDownloadedFilePath(url, PathUtil::getImageDirPath());
}

NetWorkDownloadReplyHolder *DownloadUtil::downloadInstaller(QObject *owner, const QString &url)
{
    qInfo("downloadInstaller url:%s", qUtf8Printable(url));
    return HttpMgr::instance()->download(owner, url, PathUtil::getInstallerDirPath());
}

NetWorkDownloadReplyHolder *DownloadUtil::downloadZipFile(QObject *owner, const QString &url)
{
    qInfo("downloadInstaller url:%s", qUtf8Printable(url));
    return HttpMgr::instance()->download(owner, url, PathUtil::getCourseDirPath());
}

NetWorkDownloadReplyHolder *DownloadUtil::downloadSound( QObject *owner, const QString &url,
                                                        const QString &_fileName )
{
    qInfo("downloadInstaller url:%s", qUtf8Printable(url));
    return HttpMgr::instance()->download( owner, url, _fileName, false );
}
