#ifndef WEEDUCOMPREHENSIONWIDGET_H
#define WEEDUCOMPREHENSIONWIDGET_H

#include <QWidget>
#include "utility/widget/weeducoursewidgetbase.h"
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
    void operaterMedia(wetalkMultipleChoices _multipleChoicesData);

private slots:
    void slot_chooseFinish();

private:
    Ui::WeeduComprehensionWidget    *ui;

    wetalkevents                    m_operateDataInfo;
    int                             m_itemNum;
    int                             m_multipleChoicesNum;

    DATA_ITEM_TYPE                  m_dataItemType;

};

#endif // WEEDUCOMPREHENSIONWIDGET_H
