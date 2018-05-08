#ifndef WEEDUCHOOSELEVELWIDGET_H
#define WEEDUCHOOSELEVELWIDGET_H

#include <QWidget>
#include "utility/jsonutil.h"

namespace Ui {
class WeeduChooseLevelWidget;
}

struct wetalkgetLevelInfo
{
    int id;
    QString name;
};

BEGIN_FROM_JSON(wetalkgetLevelInfo)
MEMBER_FROM_JSON(id)
MEMBER_FROM_JSON(name)
END_FROM_JSON()

//一键播放请求
typedef QVector<wetalkgetLevelInfo> wetalkgetLevelInfo_t;

struct wetalkgetLevelInfoList
{
    wetalkgetLevelInfo_t data;
};

BEGIN_FROM_JSON(wetalkgetLevelInfoList)
MEMBER_FROM_JSON(data)
END_FROM_JSON()


class WeeduChooseLevelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WeeduChooseLevelWidget(QWidget *parent = 0);
    ~WeeduChooseLevelWidget();

protected:
    void mouseReleaseEvent(QMouseEvent *event);

public:
signals:
    void signal_chooseLevelWidgetHide();

private:
    Ui::WeeduChooseLevelWidget *ui;
};

#endif // WEEDUCHOOSELEVELWIDGET_H
