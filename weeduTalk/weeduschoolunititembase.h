#ifndef WEEDUSCHOOLUNITITEMBASE_H
#define WEEDUSCHOOLUNITITEMBASE_H

#include <QWidget>
#include "utility/jsonutil.h"

struct wetalkgetUnitInfo
{
    int id;
    QString description;
    QString name;
    QString title;
    int accuracy;
    int completion_rate;
    int scores;
    bool unitLock;
    bool testLock;
    QString picture_url;
};

BEGIN_FROM_JSON(wetalkgetUnitInfo)
MEMBER_FROM_JSON(id)
MEMBER_FROM_JSON(description)
MEMBER_FROM_JSON(name)
MEMBER_FROM_JSON(title)
MEMBER_FROM_JSON(accuracy)
MEMBER_FROM_JSON(completion_rate)
MEMBER_FROM_JSON(scores)
MEMBER_FROM_JSON(unitLock)
MEMBER_FROM_JSON(testLock)
MEMBER_FROM_JSON(picture_url)
END_FROM_JSON()

//一键播放请求
typedef QVector<wetalkgetUnitInfo> wetalkgetUnitInfo_t;

struct wetalkgetUnitInfoList
{
    wetalkgetUnitInfo_t data;
};

BEGIN_FROM_JSON(wetalkgetUnitInfoList)
MEMBER_FROM_JSON(data)
END_FROM_JSON()

enum UNIT_WEEDUSCHOOL_TYPE
{
    HIGHSCHOOL_UNIT_ITEM = 0,
    MIDDLESCHOOL_UNIT_ITEM,
    PRIMARYSCHOOL_UNIT_ITEM,
};

class WeeduSchoolUnitItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit WeeduSchoolUnitItemBase(QWidget *parent = nullptr);

    virtual void bind( const wetalkgetUnitInfo _wetalkgetUnitInfo );

    static WeeduSchoolUnitItemBase *newSchoolUnitItem( QWidget *owner, const UNIT_WEEDUSCHOOL_TYPE _unitType );

protected:
    void mouseReleaseEvent(QMouseEvent *event);

public:
    void setWeeduSchoolId(const int _id);
signals:
    void signal_clickSchoolUnitItem( const int _id, const UNIT_WEEDUSCHOOL_TYPE _type );

signals:

public slots:

private:
    int                                 m_weeduSchoolId;
    static UNIT_WEEDUSCHOOL_TYPE        m_weeduSchoolType;
};

#endif // WEEDUSCHOOLUNITITEMBASE_H
