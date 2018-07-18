#ifndef WEEDUCOURSEMAINWIDGET_H
#define WEEDUCOURSEMAINWIDGET_H

#include <QWidget>
#include "utility/widget/bottomcontrolwidget.h"
#include "utility/widget/headcontrolwidget.h"
#include "utility/widget/topcontrolwidget.h"
#include "utility/widget/basemainwidget.h"
#include "utility/widget/weeducoursewidgetbase.h"

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
    void selectUIWithDatasourceAndCurrentStep(wetalkevents_t datasource, int currentStep);

    void setChooseLesson( const int _lessonNum, const int _curIndex );
signals:
    void signal_currentCourseFinish();

private:
    void init();
    void nextOperate(const int _operateNum);

private slots:
    void slot_playNext();
    void slot_playPrev();
    void slot_palyPause();

    void slot_chooseFinish();

    void slot_currentCourseFinish();
private:
    Ui::WeeduCourseMainWidget *ui;

    WeeduCourseWidgetBase           *m_currentOperateWidget;

    BottomControlWidget             *m_bottomControlWidget;
    HeadControlWidget               *m_headControlWidget;
    TopControlWidget                *m_topControlWidget;

    int                             m_currentOperateNum;
    wetalkevents_t                  m_currentOperateData;

};

#endif // WEEDUCOURSEMAINWIDGET_H
