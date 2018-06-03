#include "downlodewidget.h"
#include "ui_downlodewidget.h"
#include "zlib/zlibutility.h"
#include "utility/widget/promptmessagewidget.h"

downlodeWidget::downlodeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::downlodeWidget)
{
    ui->setupUi(this);

    setWindowFlags( Qt::FramelessWindowHint|Qt::Dialog|Qt::Tool );

    this->hide();
}

downlodeWidget::~downlodeWidget()
{
    delete ui;
}

void downlodeWidget::downlodeFile(const QString _fileUrl)
{
    qInfo("upgrade");

    if( _fileUrl.isEmpty() )
        return;

    downloadReply = DownloadUtil::downloadZipFile(this, _fileUrl);
    connect(downloadReply, &NetWorkDownloadReplyHolder::signal_onStart,
            this, &downlodeWidget::slot_onStart_download);
    connect(downloadReply, &NetWorkDownloadReplyHolder::signal_onFinish, this,
            &downlodeWidget::slot_onFinish_download);
    connect(downloadReply, &NetWorkDownloadReplyHolder::signal_onSuccess, this,
            &downlodeWidget::slot_onSuccess_download);
    connect(downloadReply, &NetWorkDownloadReplyHolder::signal_onFailure, this,
            &downlodeWidget::slot_onFailure_download);
    connect(downloadReply, &NetWorkDownloadReplyHolder::signal_downloadProgress, this,
            &downlodeWidget::slot_downloadProgress_download);
}

void downlodeWidget::slot_onStart_download()
{
    this->show();
}

void downlodeWidget::slot_onFinish_download()
{

}

void downlodeWidget::slot_onSuccess_download(const QString &filePath)
{
    QStringList _fileList;

    ZlibUtility::uncompressedFile( filePath, _fileList );

    this->hide();

    emit signal_downloadZipFileSuccess();
}

void downlodeWidget::slot_onFailure_download(int errorCode)
{
//    promptMessageWidget::ShowMsg( "资源下载失败，请重试...", this, 3 );
    this->hide();
}

void downlodeWidget::slot_downloadProgress_download(double percent, qint64, qint64)
{
    ui->progressBar->setValue((int)percent);
}
