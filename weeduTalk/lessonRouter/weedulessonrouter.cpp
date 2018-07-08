#include "weedulessonrouter.h"
#include <QDebug>
#include <PartUI/welisteningwidget.h>

WeeduLessonRouter::WeeduLessonRouter(QObject *parent) : QObject(parent)
{
}

void WeeduLessonRouter::showRouterWithClassInfoAndWidget(wetalkgetClassInfo _classInfo, QWidget *_widget)
{
    if (_classInfo.events.size() > 0)
    {
        selectUIWithDatasource(_classInfo.events , 0);
    }
    if (_classInfo.dataList.size() > 0)
    {
        selectUIWithDatasource(_classInfo.events , 0);
    }

}

void WeeduLessonRouter::selectUIWithDatasource(wetalkevents_t datasource, int currentStep)
{
    wetalkevents eventInfo = datasource[currentStep];
    if (eventInfo.type == "passage_listening") {
        WeListeningWidget listenView =  new WeListeningWidget;
        listenView.renderWithEventInfo(eventInfo);

    } else if (eventInfo.type == "passage_comprehension") {

    } else if (eventInfo.type == "passage_reading") {

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
