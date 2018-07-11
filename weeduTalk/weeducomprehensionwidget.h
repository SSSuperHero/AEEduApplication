#ifndef WEEDUCOMPREHENSIONWIDGET_H
#define WEEDUCOMPREHENSIONWIDGET_H

#include <QWidget>
#include "utility/widget/weeducoursewidgetbase.h"
#include "utility/widget/bottomcontrolwidget.h"
#include "utility/widget/headcontrolwidget.h"
#include "utility/widget/topcontrolwidget.h"
#include "weedulessonguidewidget.h"

namespace Ui {
class WeeduComprehensionWidget;
}

class WeeduComprehensionWidget : public WeeduCourseWidgetBase
{
    Q_OBJECT

public:
    explicit WeeduComprehensionWidget(QWidget *parent = 0);
    ~WeeduComprehensionWidget();

    void init();
    void loadData(const wetalkevents _dataInfo, const int _currentOperateNum);
private slots:
    void slot_playNext();
private:
    Ui::WeeduComprehensionWidget *ui;

    BottomControlWidget             *m_bottomControlWidget;
    HeadControlWidget               *m_headControlWidget;
    TopControlWidget                *m_topControlWidget;

    wetalkevents                    m_operateDataInfo;
    int                             m_crrentOperateNum;
};

#endif // WEEDUCOMPREHENSIONWIDGET_H
