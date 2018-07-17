#include "welisteningwidget.h"
#include "ui_welisteningwidget.h"
#include "mgr/media/mediaplaymanager.h"
#include "lessonRouter/weedulessonrouter.h"
#include "utility/stringutility.h"

WeListeningWidget::WeListeningWidget(QWidget *parent) :
    WeeduCourseWidgetBase(parent),
    ui(new Ui::WeListeningWidget)
{
    ui->setupUi(this);
//    ui->contentLabel->setHidden(true);

//    init();
}

WeListeningWidget::~WeListeningWidget()
{

    delete ui;
}

void WeListeningWidget::init()
{

}

void WeListeningWidget::loadData(const wetalkevents _dataInfo, const int _currentOperateNum)
{
//    ui->contentLabel->setText(eventInfo.content);
    //单个eventinfo，先通过media_type解析根事件内容，然后clickEvents(可选)，然后childEvents(可选)，最后selectEvents(可选)

    m_currentOperateNum = _currentOperateNum;

    if (_dataInfo.media_type == "audio")
    {

    }
    else if (_dataInfo.media_type == "video")
    {
        QString _videoFile = WeeduLessonRouter::instance()->getCourseResourceFilePath() + "/" + _dataInfo.media_filename;

        int _startTime = 0;
        int _endTime = 0;
        StringUtility::stringToTime( _dataInfo.timeRange, _startTime, _endTime );
        qDebug()<<"WeListeningWidget timeRange:"<<_dataInfo.timeRange <<_startTime <<_endTime;
        m_videoWidget =  MediaPlayManager::instance()->startPlayMidea( _videoFile, _startTime, _endTime  );

        ui->labelPic->hide();
        ui->widgetChooseItem->hide();
        ui->horizontalLayout->addWidget( m_videoWidget );

    }
    else if (_dataInfo.media_type == "image")
    {

    }
    else if (_dataInfo.media_type == "mouth")
    {

    }
}

