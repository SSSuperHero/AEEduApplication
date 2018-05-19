#ifndef WEEDULESSONITEMBASE_H
#define WEEDULESSONITEMBASE_H

#include <QWidget>
#include "utility/jsonutil.h"

struct wetalkgetLessonInfo
{
    int id;
    QString description;
    QString name;
    double  accuracy;
    double  completion_rate;
    int scores;
    bool lessonLock;
    bool testLock;
    QString type;
    QString picture_url;
    QString zip_url;
};

BEGIN_FROM_JSON(wetalkgetLessonInfo)
MEMBER_FROM_JSON(id)
MEMBER_FROM_JSON(description)
MEMBER_FROM_JSON(name)
MEMBER_FROM_JSON(accuracy)
MEMBER_FROM_JSON(completion_rate)
MEMBER_FROM_JSON(scores)
MEMBER_FROM_JSON(lessonLock)
MEMBER_FROM_JSON(testLock)
MEMBER_FROM_JSON(type)
MEMBER_FROM_JSON(picture_url)
MEMBER_FROM_JSON(zip_url)
END_FROM_JSON()

//一键播放请求
typedef QVector<wetalkgetLessonInfo> wetalkgetLessonInfo_t;

struct wetalkgetLessonInfoList
{
    wetalkgetLessonInfo_t data;
};

BEGIN_FROM_JSON(wetalkgetLessonInfoList)
MEMBER_FROM_JSON(data)
END_FROM_JSON()


enum LESSON_WEEDUSCHOOL_TYPE
{
    HIGHSCHOOL_LESSON_ITEM = 0,
    MIDDLESCHOOL_LESSON_ITEM,
    PRIMARYSCHOOL_LESSON_ITEM
};

class WeeduLessonItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit WeeduLessonItemBase(QWidget *parent = nullptr);

    virtual void bind( const wetalkgetLessonInfo _wetalkgetLessonInfo );

    static WeeduLessonItemBase *newSchoolLessonItem( QWidget *owner, const LESSON_WEEDUSCHOOL_TYPE _lessonType );

protected:
    void mouseReleaseEvent(QMouseEvent *event);

public:
    void setWeeduSchooLessonlId(const wetalkgetLessonInfo _lessonInfo);
signals:
    void signal_clickSchoolLessonItem( const int _id, const LESSON_WEEDUSCHOOL_TYPE _type );

public slots:

private:
    int                                 m_weeduSchoolId;
    static LESSON_WEEDUSCHOOL_TYPE      m_weeduSchoolType;

    wetalkgetLessonInfo                 m_wetalkgetLessonInfo;
};
#endif // WEEDULESSONITEMBASE_H
