#ifndef WEEDULESSONGUIDEWIDGET_H
#define WEEDULESSONGUIDEWIDGET_H

#include <QWidget>
#include "weedulessonitembase.h"

namespace Ui {
class WeEduLessonGuideWidget;
}

class WeEduLessonGuideWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WeEduLessonGuideWidget(QWidget *parent = 0);
    ~WeEduLessonGuideWidget();
    void setLessonInfoAndType (const wetalkgetLessonInfo _lessonInfo, const LESSON_WEEDUSCHOOL_TYPE _lessonType);

protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_listenButton_clicked();

    void on_readButton_clicked();

    void on_quizButton_clicked();

private:
    Ui::WeEduLessonGuideWidget *ui;
};

#endif // WEEDULESSONGUIDEWIDGET_H
