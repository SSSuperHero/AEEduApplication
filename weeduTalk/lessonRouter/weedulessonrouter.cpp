#include "weedulessonrouter.h"
#include <QDebug>
#include <PartUI/welisteningwidget.h>
#include "weeducomprehensionwidget.h"

WeeduLessonRouter::WeeduLessonRouter(QObject *parent) :
    QObject(parent),
    m_currentDataType( CLASS_INFO_ENVENS )
{
}

void WeeduLessonRouter::showRouterWithClassInfoAndWidget(wetalkgetClassInfo _classInfo, QWidget *_widget)
{

    qDebug()<<_classInfo.media_filename;

    if (_classInfo.events.size() > 0)
    {
        selectUIWithDatasourceAndCurrentStep(_classInfo.events , 3);
    }
    if (_classInfo.dataList.size() > 0)
    {
        selectUIWithDatasourceAndCurrentStep(_classInfo.dataList , 0);
    }
}

void WeeduLessonRouter::selectUIWithDatasourceAndCurrentStep(wetalkevents_t datasource, int currentStep)
{
    if( datasource.size() <= currentStep )
        return;

    wetalkevents eventInfo = datasource.at(currentStep);
    if (eventInfo.type == "passage_listening") {
        WeListeningWidget *listenView =  new WeListeningWidget;
        listenView->renderWithEventInfo(eventInfo);
        listenView->show();

    } else if (eventInfo.type == "passage_comprehension") {
        WeeduComprehensionWidget *_comprehensionWidget =  new WeeduComprehensionWidget;
        _comprehensionWidget->initDataInfo(eventInfo);
        _comprehensionWidget->show();

    } else if (eventInfo.type.contains("multipleChoices",Qt::CaseSensitive)) {
        WeeduComprehensionWidget *_comprehensionWidget =  new WeeduComprehensionWidget;
        _comprehensionWidget->initDataInfo(eventInfo);
        _comprehensionWidget->show();

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
}
