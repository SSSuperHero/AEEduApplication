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

enum DATA_ITEM_TYPE
{
    DATA_ITEM,
    DATA_SELECT,
    DATA_MULTIPLECHOICES
};

class WeeduComprehensionWidget : public WeeduCourseWidgetBase
{
    Q_OBJECT

public:
    explicit WeeduComprehensionWidget(QWidget *parent = 0);
    ~WeeduComprehensionWidget();

    void init();
    void loadData(const wetalkevents _dataInfo, const int _currentOperateNum);

private:
    void showItems();
    void showSelect();
    void operaterMedia(const QString _mediaType, const QString _mediaFile);

private slots:
    void slot_playNext();
    void slot_playPrev();
    void slot_palyPause();

private:
    Ui::WeeduComprehensionWidget *ui;

    BottomControlWidget             *m_bottomControlWidget;
    HeadControlWidget               *m_headControlWidget;
    TopControlWidget                *m_topControlWidget;

    wetalkevents                    m_operateDataInfo;
    int                             m_crrentOperateNum;
    int                             m_itemNum;
    int                             m_multipleChoicesNum;

    DATA_ITEM_TYPE                  m_dataItemType;

};

#endif // WEEDUCOMPREHENSIONWIDGET_H
