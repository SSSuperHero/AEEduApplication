#include "weedulessonrouter.h"
#include <QDebug>

WeeduLessonRouter::WeeduLessonRouter(QObject *parent) : QObject(parent)
{

}

void WeeduLessonRouter::showRouterWithClassInfoAndWidget(wetalkgetClassInfo _classInfo, QWidget *_widget)
{
        qDebug()<<_classInfo.media_filename;
}
