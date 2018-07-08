#include "welisteningwidget.h"
#include "ui_welisteningwidget.h"

WeListeningWidget::WeListeningWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeListeningWidget)
{
    ui->setupUi(this);
    ui->contentLabel->setHidden(true);
}

WeListeningWidget::~WeListeningWidget()
{
    delete ui;
}

WeListeningWidget::init()
{
    m_bottomControlWidget = new BottomControlWidget( this );
    m_headControlWidget = new HeadControlWidget( this );
    m_topControlWidget = new TopControlWidget( this );

}

void WeListeningWidget::renderWithEventInfo(wetalkevents eventInfo)
{
    ui->contentLabel->setText(eventInfo.content);
    //单个eventinfo，先通过media_type解析根事件内容，然后clickEvents(可选)，然后childEvents(可选)，最后selectEvents(可选)
    if (eventInfo.media_type == "audio") {

    } else if (eventInfo.media_type == "video") {

    } else if (eventInfo.media_type == "image") {

    } else  if (eventInfo.media_type == "mouth"){

    }
}

void WeListeningWidget::on_showContentButton_clicked()
{
    ui->contentLabel->setHidden(false);
}
