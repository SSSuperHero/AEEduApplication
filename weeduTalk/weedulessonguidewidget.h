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

private:
    Ui::WeEduLessonGuideWidget *ui;
};

#endif // WEEDULESSONGUIDEWIDGET_H
