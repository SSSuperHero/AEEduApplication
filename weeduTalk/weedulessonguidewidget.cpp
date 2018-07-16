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
}

void WeEduLessonGuideWidget::loadData( const wetalkgetPartInfo_t _partInfoList )
{
    if( _partInfoList.size() == 0 )
        return;

    clearLayout( ui->verticalLayoutPartList );

//
    DownloadUtil::downloadImage(this, _partInfoList.at(0).picture_url, ui->lessonCover,
                                "QLabel#lessonCover", false );
    foreach (  wetalkgetPartInfo _partInfo, _partInfoList )
    {
        ClickedLabel *_partItem = new ClickedLabel( _partInfo.name, this );
        _partItem->setInfoId( _partInfo.id );

        _partItem->setStyleSheet( " QLabel{color:#000000; border-radius:2px;} \
        QLabel:hover{color:#666666;}");

        ui->verticalLayoutPartList->addWidget( _partItem );

        connect( _partItem, &ClickedLabel::Clicked, this, &WeEduLessonGuideWidget::slot_clickPartItem );
    }

}

void WeEduLessonGuideWidget::analysisPartJson( const int _partId )
{
    QString _jsonFile = m_filePath + "/" + QString("json%1.txt").arg(_partId);

    qDebug()<<"analysisPartJson:"<<_jsonFile;
    QFile fp( _jsonFile );
    if(fp.open(QIODevice::ReadOnly))
    {
        QByteArray bt = fp.readAll();

        QString jsonString = bt;

        wetalkgetClassInfo _classInfo;
        fromJson( jsonString, _classInfo );

        WeeduLessonRouter *router = WeeduLessonRouter::instance();
        router->setCourseResourceFilePath( m_filePath );
        router->showRouterWithClassInfoAndWidget(_classInfo, this);
    }
    fp.close();
}

void WeEduLessonGuideWidget::mouseReleaseEvent(QMouseEvent *event)
{
    this->hide();
}

void WeEduLessonGuideWidget::slot_clickPartItem( ClickedLabel *_partItem )
{
    analysisPartJson( _partItem->getInfoId() );

    emit signal_currentCourseFinish( false );
}

void WeEduLessonGuideWidget::slot_courseFinish()
{
//    this->show();
    emit signal_currentCourseFinish( true );
}
