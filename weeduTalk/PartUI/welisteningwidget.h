#ifndef WELISTENINGWIDGET_H
#define WELISTENINGWIDGET_H

#include <QWidget>
#include <weedulessonguidewidget.h>
#include <utility/widget/bottomcontrolwidget.h>
#include <utility/widget/headcontrolwidget.h>
#include <utility/widget/topcontrolwidget.h>
#include "utility/widget/weeducoursewidgetbase.h"

namespace Ui {
class WeListeningWidget;
}

class WeListeningWidget : public WeeduCourseWidgetBase
{
    Q_OBJECT

public:
    explicit WeListeningWidget(QWidget *parent = 0);
    ~WeListeningWidget();

    void loadData(const wetalkevents _dataInfo, const int _currentOperateNum);
private:
    void init();

private slots:
    void on_showContentButton_clicked();

    void slot_playNext();
private:
    Ui::WeListeningWidget                   *ui;
    BottomControlWidget                     *m_bottomControlWidget;
    HeadControlWidget                       *m_headControlWidget;
    TopControlWidget                        *m_topControlWidget;

    int                                     m_currentOperateNum;
};

#endif // WELISTENINGWIDGET_H
