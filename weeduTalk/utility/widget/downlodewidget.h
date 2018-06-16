#ifndef DOWNLODEWIDGET_H
#define DOWNLODEWIDGET_H

#include <QWidget>
#include "mybasesingleton.h"
#include "utility/downloadutil.h"

namespace Ui {
class downlodeWidget;
}

class downlodeWidget : public QWidget
{
    Q_OBJECT

#ifdef Q_OS_MAC
    MY_DECLARE_SINGLETON(downlodeWidget)
#else
    DECLARE_SINGLETON(downlodeWidget)
    // SingletonMgrBase interface
#endif

public:
    explicit downlodeWidget(QWidget *parent = 0);
    ~downlodeWidget();

public:
signals:
    void signal_downloadZipFileSuccess( QString filePath, const int _fileId );

public:
//    void upgrade(const UpdataInfo &data);
    void downlodeFile(const QString _fileUrl , const int _fileId);

private slots:
    void slot_onStart_download();
    void slot_onFinish_download();
    void slot_onSuccess_download(const QString &filePath);
    void slot_onFailure_download(int errorCode);
    void slot_downloadProgress_download(double percent, qint64, qint64);

private:
    Ui::downlodeWidget              *ui;

    NetWorkDownloadReplyHolder      *downloadReply;

    int                             m_downlodeFileId;
};

#endif // DOWNLODEWIDGET_H
