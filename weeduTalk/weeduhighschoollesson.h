#ifndef WEEDUHIGHSCHOOLLESSON_H
#define WEEDUHIGHSCHOOLLESSON_H

#include <QWidget>
#include "weedulessonitembase.h"

namespace Ui {
class WeeduHighSchoolLesson;
}

class WeeduHighSchoolLesson : public WeeduLessonItemBase
{
    Q_OBJECT

public:
    explicit WeeduHighSchoolLesson(QWidget *parent = 0);
    ~WeeduHighSchoolLesson();

    void bind( const wetalkgetLessonInfo _wetalkgetLessonInfo );

private:
    Ui::WeeduHighSchoolLesson *ui;
};

#endif // WEEDUHIGHSCHOOLLESSON_H
