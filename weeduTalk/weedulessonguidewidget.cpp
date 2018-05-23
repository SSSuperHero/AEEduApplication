#include "weedulessonguidewidget.h"
#include "ui_weedulessonguidewidget.h"
#include "utility/downloadutil.h"
#include <QPainter>

WeEduLessonGuideWidget::WeEduLessonGuideWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeEduLessonGuideWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint );
    setAttribute(Qt::WA_TranslucentBackground, true);

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

void WeEduLessonGuideWidget::on_listenButton_clicked()
{

}

void WeEduLessonGuideWidget::on_readButton_clicked()
{

}

void WeEduLessonGuideWidget::on_quizButton_clicked()
{

}
