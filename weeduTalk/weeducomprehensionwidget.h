#ifndef WEEDUCOMPREHENSIONWIDGET_H
#define WEEDUCOMPREHENSIONWIDGET_H

#include <QWidget>
#include "utility/widget/basemainwidget.h"
#include "utility/widget/bottomcontrolwidget.h"
#include "utility/widget/headcontrolwidget.h"
#include "utility/widget/topcontrolwidget.h"
#include "weedulessonguidewidget.h"

namespace Ui {
class WeeduComprehensionWidget;
}

class WeeduComprehensionWidget : public BaseMainWidget
{
    Q_OBJECT

public:
    explicit WeeduComprehensionWidget(QWidget *parent = 0);
    ~WeeduComprehensionWidget();

    void init();
    void initDataInfo(const wetalkevents _dataInfo);
private:
    Ui::WeeduComprehensionWidget *ui;

    BottomControlWidget             *m_bottomControlWidget;
    HeadControlWidget               *m_headControlWidget;
    TopControlWidget                *m_topControlWidget;

    wetalkevents                    m_operateDataInfo;
};

#endif // WEEDUCOMPREHENSIONWIDGET_H
