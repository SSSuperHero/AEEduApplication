#ifndef WEEDUCOURSEMAINWIDGET_H
#define WEEDUCOURSEMAINWIDGET_H

#include <QWidget>
#include "utility/widget/bottomcontrolwidget.h"
#include "utility/widget/headcontrolwidget.h"
#include "utility/widget/topcontrolwidget.h"
#include "utility/widget/basemainwidget.h"

namespace Ui {
class WeeduCourseMainWidget;
}

class WeeduCourseMainWidget : public BaseMainWidget
{
    Q_OBJECT

public:
    explicit WeeduCourseMainWidget(QWidget *parent = 0);
    ~WeeduCourseMainWidget();

    void addWidget(QWidget *_courseShowWidget);
signals:
    void signal_palyPause();
    void signal_playPrev();
    void signal_playNext();

    void signal_currentOperateFinish( const int _nextOperateNum );
    void signal_currentCourseFinish();

private:
    void init();

private slots:
    void slot_playNext();
    void slot_playPrev();
    void slot_palyPause();

    void slot_chooseFinish();

private:
    Ui::WeeduCourseMainWidget *ui;

    BottomControlWidget             *m_bottomControlWidget;
    HeadControlWidget               *m_headControlWidget;
    TopControlWidget                *m_topControlWidget;

    int                             m_crrentOperateNum;

};

#endif // WEEDUCOURSEMAINWIDGET_H
