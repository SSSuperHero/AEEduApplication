#include "networkimagereplyholder.h"
#include "utility/widget/imageutil.h"


NetworkImageReplyBuilder::NetworkImageReplyBuilder()
{

}

NetworkImageReplyBuilder &NetworkImageReplyBuilder::setWidget(QWidget *widget_)
{
    widget = widget_;

    return *this;
}

NetworkImageReplyBuilder &NetworkImageReplyBuilder::setInitImagePath(const QString &imagePath)
{
    initImagePath = imagePath;

    return *this;
}

NetworkImageReplyBuilder &NetworkImageReplyBuilder::setFailedImagePath(const QString &imagePath)
{
    failedImagePath = imagePath;

    return *this;
}

NetworkImageReplyBuilder &NetworkImageReplyBuilder::setStyleSheetSectionName(const QString &styleSheetSectionName_)
{
    styleSheetSectionName = styleSheetSectionName_;

    return *this;
}

NetworkImageReplyBuilder &NetworkImageReplyBuilder::setIsBackgroundImage(bool bBackgroundImage_)
{
    bBackgroundImage = bBackgroundImage_;

    return *this;
}


NetworkImageReplyHolder::NetworkImageReplyHolder(QObject* owner, NetWorkDownloadReplyHolder* reply_, const NetworkImageReplyBuilder& builder_)
    : QObject(owner)
    , reply(reply_)
    , builder(builder_)

{
    connect(reply, &NetWorkDownloadReplyHolder::signal_onStart, this, &NetworkImageReplyHolder::slot_onStart);
//    connect(reply, &NetWorkDownloadReplyHolder::signal_onFinish, this, &NetworkImageReplyHolder::slot_onFinish);
    connect(reply, &NetWorkDownloadReplyHolder::signal_onSuccess, this, &NetworkImageReplyHolder::slot_onSuccess);
    connect(reply, &NetWorkDownloadReplyHolder::signal_onFailure, this, &NetworkImageReplyHolder::slot_onFailure);
}

void NetworkImageReplyHolder::slot_onSuccess(const QString& filePath)
{
    qInfo("signal_onSuccess filePath:%s", qUtf8Printable(filePath));

    ImageUtil::setBackgroundImage(builder.widget, builder.styleSheetSectionName, filePath, builder.bBackgroundImage);

    emit signal_onSuccess(filePath);
}

void NetworkImageReplyHolder::slot_onFailure(int errorCode)
{
    qInfo("slot_onFailure errorCode:%d", errorCode);
    if (!builder.failedImagePath.isEmpty() && QFile::exists(builder.failedImagePath))
    {
        ImageUtil::setBackgroundImage(builder.widget, builder.styleSheetSectionName, builder.failedImagePath, builder.bBackgroundImage);
    }

    emit signal_onFailure(errorCode);
}

void NetworkImageReplyHolder::slot_onStart()
{
    qInfo("slot_onStart...");

    if (!builder.initImagePath.isEmpty() && QFile::exists(builder.initImagePath))
    {
        ImageUtil::setBackgroundImage(builder.widget, builder.styleSheetSectionName, builder.initImagePath, builder.bBackgroundImage);
    }

    emit signal_onStart();
}

void NetworkImageReplyHolder::slot_onFinish()
{
    qInfo("delteLater");
//    this->deleteLater();

    emit signal_onFinish();
}
