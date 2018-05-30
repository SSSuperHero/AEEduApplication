#ifndef WEEDUCHOOSELEVELITEM_H
#define WEEDUCHOOSELEVELITEM_H

#include <QWidget>
#include "utility/jsonutil.h"

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


namespace Ui {
class WeeduChooseLevelItem;
}

class WeeduChooseLevelItem : public QWidget
{
    Q_OBJECT

public:
    explicit WeeduChooseLevelItem(QWidget *parent = 0);
    ~WeeduChooseLevelItem();

    void bind(const wetalkgetLevelInfo _levelInfo , const int _num);

private:
    void setBackgroundPic(const int _num);
    void mouseReleaseEvent(QMouseEvent *event);

public:
signals:
    void signal_clickWeeduChooseLevelItem( const int _leaveId );
private:
    Ui::WeeduChooseLevelItem            *ui;

    wetalkgetLevelInfo                  m_wetalkgetLeveInfo;
};

#endif // WEEDUCHOOSELEVELITEM_H
