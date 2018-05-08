#ifndef NETWORKIMAGEREPLYHOLDER_H
#define NETWORKIMAGEREPLYHOLDER_H

#include "NetWorkDownloadReplyHolder.h"
#include <QLabel>

struct NetworkImageReplyBuilder
{
    NetworkImageReplyBuilder();

    NetworkImageReplyBuilder& setWidget(QWidget* widget);
    NetworkImageReplyBuilder& setInitImagePath(const QString& imagePath);
    NetworkImageReplyBuilder& setFailedImagePath(const QString& imagePath);
    NetworkImageReplyBuilder& setStyleSheetSectionName(const QString& styleSheetSectionName);
    NetworkImageReplyBuilder& setIsBackgroundImage(bool bBackgroundImage);


    QWidget* widget;
    QString  initImagePath;
    QString  failedImagePath;
    QString  styleSheetSectionName;
    bool     bBackgroundImage;
};

class NetworkImageReplyHolder: public QObject
{
    Q_OBJECT
public:
    NetworkImageReplyHolder(QObject* owner, NetWorkDownloadReplyHolder* reply, const NetworkImageReplyBuilder& builder);


signals:
    void signal_onStart();
    void signal_onFinish();
    void signal_onSuccess(const QString& filePath);
    void signal_onFailure(int errorCode);

private slots:
    void slot_onStart();
    void slot_onFinish();
    void slot_onSuccess(const QString& filePath);
    void slot_onFailure(int errorCode);


private:
    NetWorkDownloadReplyHolder* reply;
    NetworkImageReplyBuilder    builder;
};

#endif // NETWORKIMAGEREPLYHOLDER_H
