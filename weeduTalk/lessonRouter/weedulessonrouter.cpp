#include "weedulessonrouter.h"
#include <QDebug>
#include <PartUI/welisteningwidget.h>
#include "weeducomprehensionwidget.h"

WeeduLessonRouter::WeeduLessonRouter(QObject *parent) :
    QObject(parent),
    m_currentDataType( CLASS_INFO_ENVENS ),
    m_currentOperateWidget(NULL),
    m_courseResourceFilePath("")
{
    m_weeduCourseMainWidget = new WeeduCourseMainWidget();
}

void WeeduLessonRouter::showRouterWithClassInfoAndWidget(wetalkgetClassInfo _classInfo, QWidget *_widget)
{

    qDebug()<<_classInfo.media_type;

    if (_classInfo.events.size() > 0)
    {
        selectUIWithDatasourceAndCurrentStep(_classInfo.events , 0);
        m_currentOperateData = _classInfo.events;
    }
    else if (_classInfo.dataList.size() > 0)
    {
        selectUIWithDatasourceAndCurrentStep(_classInfo.dataList , 0);
        m_currentOperateData = _classInfo.dataList;
    }
}

void WeeduLessonRouter::selectUIWithDatasourceAndCurrentStep(wetalkevents_t datasource, int currentStep)
{
    if( datasource.size() <= currentStep )
        return;

    if( m_currentOperateWidget )
    {
        m_currentOperateWidget->deleteLater();
        m_currentOperateWidget = NULL;
    }

    wetalkevents eventInfo = datasource.at(currentStep);
    if (eventInfo.type == "passage_listening") {
        m_currentOperateWidget =  new WeListeningWidget;
        m_currentOperateWidget->loadData(eventInfo,currentStep);
        m_currentOperateWidget->show();

    } else if (eventInfo.type == "passage_comprehension") {
        m_currentOperateWidget =  new WeeduComprehensionWidget;
        m_currentOperateWidget->loadData(eventInfo,currentStep);
        m_weeduCourseMainWidget->addWidget( m_currentOperateWidget );
        m_weeduCourseMainWidget->show();

    } else if (eventInfo.type.contains("multipleChoices",Qt::CaseSensitive)) {
        m_currentOperateWidget =  new WeeduComprehensionWidget;
        m_currentOperateWidget->loadData(eventInfo,currentStep);
        m_weeduCourseMainWidget->addWidget( m_currentOperateWidget );
        m_weeduCourseMainWidget->show();

    } else if (eventInfo.type == "dialog_listening") {

    } else if (eventInfo.type == "dialog_comprehension") {

    } else if (eventInfo.type == "dialog_interaction") {

    } else if (eventInfo.type == "") {

    } else if (eventInfo.type == "") {

    } else if (eventInfo.type == "") {

    } else if (eventInfo.type == "") {

    } else if (eventInfo.type == "") {

    } else if (eventInfo.type == "") {

    } else if (eventInfo.type == "") {

    } else if (eventInfo.type == "") {

    } else {

    }

    if( m_currentOperateWidget )
    {
        connect( m_currentOperateWidget, &WeeduCourseWidgetBase::signal_currentOperateFinish,
                 this, &WeeduLessonRouter::slot_nextOperate );
        connect( m_currentOperateWidget, &WeeduCourseWidgetBase::signal_currentCourseFinish,
                 this, &WeeduLessonRouter::slot_currentCourseFinish );
    }
}

void WeeduLessonRouter::slot_nextOperate( const int _operateNum )
{
    qDebug()<<" m_currentOperateData size:"<<m_currentOperateData.size();
    qDebug()<<" m_currentOperateData _operateNum:"<<_operateNum;

    if( m_currentOperateData.size() <= _operateNum )
    {
        slot_currentCourseFinish();
        return;
    }

    selectUIWithDatasourceAndCurrentStep( m_currentOperateData, _operateNum );
}

void WeeduLessonRouter::slot_currentCourseFinish()
{
    if( m_currentOperateWidget )
    {
        m_currentOperateWidget->close();
        m_currentOperateWidget->deleteLater();
        m_currentOperateWidget = NULL;
    }

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
