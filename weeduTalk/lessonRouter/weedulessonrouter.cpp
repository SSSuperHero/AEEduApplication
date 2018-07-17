#include "weedulessonrouter.h"
#include <QDebug>
#include <PartUI/welisteningwidget.h>
#include "weeducomprehensionwidget.h"

WeeduLessonRouter::WeeduLessonRouter(QObject *parent) :
    QObject(parent),
    m_currentDataType( CLASS_INFO_ENVENS ),
    m_courseResourceFilePath("")
{
    m_weeduCourseMainWidget = new WeeduCourseMainWidget();

    connect( m_weeduCourseMainWidget, &WeeduCourseMainWidget::signal_currentCourseFinish,
             this, &WeeduLessonRouter::slot_currentCourseFinish );
}

void WeeduLessonRouter::showRouterWithClassInfoAndWidget(wetalkgetClassInfo _classInfo)
{

    qDebug()<<_classInfo.media_type;

    if (_classInfo.events.size() > 0)
    {
        m_weeduCourseMainWidget->selectUIWithDatasourceAndCurrentStep(_classInfo.events , 0);
        m_currentOperateData = _classInfo.events;
    }
    else if (_classInfo.dataList.size() > 0)
    {
        m_weeduCourseMainWidget->selectUIWithDatasourceAndCurrentStep(_classInfo.dataList , 0);
        m_currentOperateData = _classInfo.dataList;
    }
}

void WeeduLessonRouter::slot_currentCourseFinish()
{
    m_weeduCourseMainWidget->hide();

    emit signal_currentCourseFinish();
}

void WeeduLessonRouter::setCourseResourceFilePath( const QString _filePath)
{
    m_courseResourceFilePath = _filePath;

    qDebug()<<" setCourseResourceFilePath _filePath:"<<_filePath;
}

QString WeeduLessonRouter::getCourseResourceFilePath()
{
    qDebug()<<" getCourseResourceFilePath _filePath:"<<m_courseResourceFilePath;

    return m_courseResourceFilePath;
}
