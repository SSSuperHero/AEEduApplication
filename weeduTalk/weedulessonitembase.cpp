#include "weedulessonitembase.h"
#include "weedulessonitem.h"
#include "weeduhighschoollesson.h"

LESSON_WEEDUSCHOOL_TYPE WeeduLessonItemBase::m_weeduSchoolType = HIGHSCHOOL_LESSON_ITEM;

WeeduLessonItemBase::WeeduLessonItemBase(QWidget *parent) : QWidget(parent)
{

}

void WeeduLessonItemBase::bind(const wetalkgetLessonInfo _wetalkgetLessonInfo)
{

}

WeeduLessonItemBase *WeeduLessonItemBase::newSchoolLessonItem(QWidget *owner, const LESSON_WEEDUSCHOOL_TYPE _lessonType)
{
    WeeduLessonItemBase * _weeduSchoolLessonItem = NULL;
    m_weeduSchoolType = _lessonType;

    switch ( _lessonType )
    {
    case HIGHSCHOOL_LESSON_ITEM:
        _weeduSchoolLessonItem = new WeeduHighSchoolLesson( owner );
        break;

    case MIDDLESCHOOL_LESSON_ITEM:
    case PRIMARYSCHOOL_LESSON_ITEM:
        _weeduSchoolLessonItem = new WeeduLessonItem( owner );
        break;

    default:
        break;
    }

    return _weeduSchoolLessonItem;
}

void WeeduLessonItemBase::mouseReleaseEvent(QMouseEvent *event)
{
    emit signal_clickSchoolLessonItem( m_weeduSchoolId, m_weeduSchoolType );

    QWidget::mouseReleaseEvent( event );
}

void WeeduLessonItemBase::setWeeduSchooLessonlId(const int _id)
{
    m_weeduSchoolId = _id;
}
