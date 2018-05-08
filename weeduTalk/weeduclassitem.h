#ifndef WEEDUCLASSITEM_H
#define WEEDUCLASSITEM_H

#include <QWidget>
#include "utility/jsonutil.h"

namespace Ui {
class WeeduClassItem;
}

struct wetalkgetCourseInfo
{
    int id;
    QString description;
    QString name;
    QString createdTime;
    QString unitCount;
    QString type;
    QString suitable_object;
    QString learning_goals;
    QString nature_course;
    QString picture_url;
};

BEGIN_FROM_JSON(wetalkgetCourseInfo)
MEMBER_FROM_JSON(id)
MEMBER_FROM_JSON(description)
MEMBER_FROM_JSON(name)
MEMBER_FROM_JSON(createdTime)
MEMBER_FROM_JSON(unitCount)
MEMBER_FROM_JSON(type)
MEMBER_FROM_JSON(suitable_object)
MEMBER_FROM_JSON(learning_goals)
MEMBER_FROM_JSON(nature_course)
MEMBER_FROM_JSON(picture_url)
END_FROM_JSON()

//一键播放请求
typedef QVector<wetalkgetCourseInfo> wetalkgetCourseInfo_t;

struct wetalkgetCourseInfoList
{
    wetalkgetCourseInfo_t data;
};

BEGIN_FROM_JSON(wetalkgetCourseInfoList)
MEMBER_FROM_JSON(data)
END_FROM_JSON()


class WeeduClassItem : public QWidget
{
    Q_OBJECT

public:
    explicit WeeduClassItem(QWidget *parent = 0);
    ~WeeduClassItem();

void bindData(const wetalkgetCourseInfo _courseInfo);

public:
signals:
    void signal_clickCourse( const int _course_id, const QString _course_type );

protected:
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::WeeduClassItem              *ui;

    wetalkgetCourseInfo             m_courseInfo;
};

#endif // WEEDUCLASSITEM_H
