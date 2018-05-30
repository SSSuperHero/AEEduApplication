#ifndef WEEDUCHOOSELEVELWIDGET_H
#define WEEDUCHOOSELEVELWIDGET_H

#include <QWidget>
#include "weeduchooselevelitem.h"
#include "utility/widget/basewidget.h"

namespace Ui {
class WeeduChooseLevelWidget;
}

class WeeduChooseLevelWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit WeeduChooseLevelWidget(QWidget *parent = 0);
    ~WeeduChooseLevelWidget();

void bindWeeduChooseLevelInfoList( const wetalkgetLevelInfo_t _levelInfoList );

protected:
    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);
public:
signals:
    void signal_chooseLevelWidgetHide();
    void signal_clickWeeduChooseLevelItem( const int _leaveId );

private:
    Ui::WeeduChooseLevelWidget      *ui;

    wetalkgetLevelInfo_t            m_WeeduChooseLevelInfoList;

    QWidget                         *m_layoutWidgetbase;
};

#endif // WEEDUCHOOSELEVELWIDGET_H
