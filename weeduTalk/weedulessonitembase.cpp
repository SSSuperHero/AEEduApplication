#include "weedulessonitembase.h"
#include "weedulessonitem.h"
#include "weeduhighschoollesson.h"
#include "utility/widget/downlodewidget.h"
#include <QDebug>

LESSON_WEEDUSCHOOL_TYPE WeeduLessonItemBase::m_weeduSchoolType = HIGHSCHOOL_LESSON_ITEM;

WeeduLessonItemBase::WeeduLessonItemBase(QWidget *parent) : QWidget(parent)
{
    connect( downlodeWidget::instance(), &downlodeWidget::signal_downloadZipFileSuccess,
             this, &WeeduLessonItemBase::slot_downloadZipFileSuccess );
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
    if ( m_weeduSchoolType > HIGHSCHOOL_LESSON_ITEM )
    {
        downlodeWidget::instance()->downlodeFile( m_wetalkgetLessonInfo.zip_url, m_wetalkgetLessonInfo.id );
    }

    QWidget::mouseReleaseEvent( event );
}

void WeeduLessonItemBase::slot_downloadZipFileSuccess( QString filePath, const int _fileId )
{
    QString _partFilePath = filePath.remove( ".zip" );

    if( _fileId == m_wetalkgetLessonInfo.id )
        emit signal_clickSchoolLessonItem( m_wetalkgetLessonInfo, m_weeduSchoolType, _partFilePath );

    qDebug()<<"slot_downloadZipFileSuccess id:"<<_fileId<<m_wetalkgetLessonInfo.id<<filePath;
}

void WeeduLessonItemBase::setWeeduSchooLessonlId(const wetalkgetLessonInfo _lessonInfo)
{
    m_wetalkgetLessonInfo = _lessonInfo;
}
