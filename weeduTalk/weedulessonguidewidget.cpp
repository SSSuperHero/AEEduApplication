#include "weedulessonguidewidget.h"
#include "ui_weedulessonguidewidget.h"
#include "utility/downloadutil.h"
#include <QPainter>
#include "utility/pathutil.h"
#include <QFile>
#include <QDebug>
#include <lessonRouter/weedulessonrouter.h>

WeEduLessonGuideWidget::WeEduLessonGuideWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::WeEduLessonGuideWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint );
    setAttribute(Qt::WA_TranslucentBackground, true);

    connect( WeeduLessonRouter::instance(), &WeeduLessonRouter::signal_currentCourseFinish,
             this, &WeEduLessonGuideWidget::slot_courseFinish );

}

WeEduLessonGuideWidget::~WeEduLessonGuideWidget()
{
    delete ui;
}

void WeEduLessonGuideWidget::setLessonInfoAndType(const wetalkgetLessonInfo _lessonInfo, const LESSON_WEEDUSCHOOL_TYPE _lessonType)
{
    DownloadUtil::downloadImage(this, _lessonInfo.picture_url, ui->lessonCover,
                                "QLabel#lessonCover", false );

}

void WeEduLessonGuideWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(0, 0, 0, 80));
}

void WeEduLessonGuideWidget::setPartFilePath( const QString _filePath )
{
    m_filePath = _filePath;

    WeeduLessonRouter::instance()->setCourseResourceFilePath( m_filePath );
}

void WeEduLessonGuideWidget::loadData( const wetalkgetPartInfo_t _partInfoList )
{
    if( _partInfoList.size() == 0 )
        return;

    clearLayout( ui->verticalLayoutPartList );

    DownloadUtil::downloadImage(this, _partInfoList.at(0).picture_url, ui->lessonCover,
                                "QLabel#lessonCover", false );

    for( int i = 0; i < _partInfoList.size(); i++ )
//    foreach (  wetalkgetPartInfo _partInfo, _partInfoList )
    {
        wetalkgetPartInfo _partInfo = _partInfoList[i];
        ClickedLabel *_partItem = new ClickedLabel( _partInfo.name, this );
        _partItem->setDataInfo( _partInfo.id, _partInfoList.size(), i );

        _partItem->setStyleSheet( "QLabel{color:#000000; border-radius:2px;} \
        QLabel:hover{color:#666666;}");

        ui->verticalLayoutPartList->addWidget( _partItem );

        connect( _partItem, &ClickedLabel::Clicked, this, &WeEduLessonGuideWidget::slot_clickPartItem );
    }
}

void WeEduLessonGuideWidget::mouseReleaseEvent(QMouseEvent *event)
{
    this->hide();
}

void WeEduLessonGuideWidget::slot_clickPartItem( ClickedLabel *_partItem )
{
    WeeduLessonRouter::instance()->analysisPartJson( _partItem->getInfoId(),
                                                     _partItem->getTotleIndex(),
                                                     _partItem->getCurrentIndex() );

    emit signal_currentCourseFinish( false );
}

void WeEduLessonGuideWidget::slot_courseFinish()
{
//    this->show();
    emit signal_currentCourseFinish( true );
}
