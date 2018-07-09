#include "weedulessonrouter.h"
#include <QDebug>

WeeduLessonRouter::WeeduLessonRouter(QObject *parent) :
    QObject(parent),
    m_currentDataType( CLASS_INFO_ENVENS )
{
}

void WeeduLessonRouter::showRouterWithClassInfoAndWidget(wetalkgetClassInfo _classInfo, QWidget *_widget)
{
    qDebug()<<_classInfo.media_filename;
}

