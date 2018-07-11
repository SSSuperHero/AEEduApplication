#include "welisteningwidget.h"
#include "ui_welisteningwidget.h"

WeListeningWidget::WeListeningWidget(QWidget *parent) :
    WeeduCourseWidgetBase(parent),
    ui(new Ui::WeListeningWidget),
    m_currentOperateNum(0)
{
    ui->setupUi(this);
//    ui->contentLabel->setHidden(true);

    init();
}

WeListeningWidget::~WeListeningWidget()
{
    delete ui;
}

void WeListeningWidget::init()
{
    m_bottomControlWidget = new BottomControlWidget( this );
    ui->horizontalLayout_bottom->addWidget( m_bottomControlWidget );
    connect( m_bottomControlWidget, &BottomControlWidget::signal_playNext,
             this, &WeListeningWidget::slot_playNext );

    m_headControlWidget = new HeadControlWidget( this );
     ui->verticalLayout_head->addWidget( m_headControlWidget );

    m_topControlWidget = new TopControlWidget( this );
    ui->verticalLayout_head->addWidget( m_topControlWidget );

}

void WeListeningWidget::slot_playNext()
{
    emit signal_currentOperateFinish( m_currentOperateNum + 1 );
}

void WeListeningWidget::loadData(const wetalkevents _dataInfo, const int _currentOperateNum)
{
//    ui->contentLabel->setText(eventInfo.content);
    //单个eventinfo，先通过media_type解析根事件内容，然后clickEvents(可选)，然后childEvents(可选)，最后selectEvents(可选)

    m_currentOperateNum = _currentOperateNum;

    if (_dataInfo.media_type == "audio") {

    } else if (_dataInfo.media_type == "video") {

    } else if (_dataInfo.media_type == "image") {

    } else  if (_dataInfo.media_type == "mouth"){

    }
}

void WeListeningWidget::on_showContentButton_clicked()
{
//    ui->contentLabel->setHidden(false);
}
