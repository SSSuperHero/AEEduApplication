#ifndef WEEDULESSONITEM_H
#define WEEDULESSONITEM_H

#include <QWidget>
#include "utility/jsonutil.h"
#include "weedulessonitembase.h"

namespace Ui {
class WeeduLessonItem;
}

class WeeduLessonItem : public WeeduLessonItemBase
{
    Q_OBJECT

public:
    explicit WeeduLessonItem(QWidget *parent = 0);

    void bind( const wetalkgetLessonInfo _wetalkgetLessonInfo );

    ~WeeduLessonItem();

private:
    Ui::WeeduLessonItem *ui;
};

#endif // WEEDULESSONITEM_H
