#ifndef WEEDULESSONROUTER_H
#define WEEDULESSONROUTER_H

#include <QObject>
#include <weedulessonguidewidget.h>
#include "mybasesingleton.h"

enum OPERATE_TYPE
{
    OPERATE_PREV,
    OPERATE_CURRENT,
    OPERATE_NEX
};

enum CLASS_INFO_TYPE
{
    CLASS_INFO_ENVENS,
    CLASS_INFO_DATALIST,
    CLASS_INFO_DATAMENU,
    CLASS_INFO_SYSTEMS,
    CLASS_INFO_RESULTS,
    CLASS_INFO_KEYWORDS
};

class WeeduLessonRouter : public QObject
{
    Q_OBJECT
    MY_DECLARE_SINGLETON(WeeduLessonRouter)
public:
    explicit WeeduLessonRouter(QObject *parent = nullptr);

    void showRouterWithClassInfoAndWidget(wetalkgetClassInfo _classInfo, QWidget *_widget);

//    void playAudio(const QString _file);

signals:

public slots:

private:
    wetalkevents_t              m_currentOperateData;
    CLASS_INFO_TYPE             m_currentDataType;
};

#endif // WEEDULESSONROUTER_H
