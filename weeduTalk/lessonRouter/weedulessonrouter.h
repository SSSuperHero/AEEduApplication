#ifndef WEEDULESSONROUTER_H
#define WEEDULESSONROUTER_H

#include <QObject>
#include <weedulessonguidewidget.h>
#include "mybasesingleton.h"

class WeeduLessonRouter : public QObject
{
    Q_OBJECT
    MY_DECLARE_SINGLETON(WeeduLessonRouter)
public:
    explicit WeeduLessonRouter(QObject *parent = nullptr);

    void showRouterWithClassInfoAndWidget(wetalkgetClassInfo _classInfo, QWidget *_widget);

    void playAudio(const QString _file);

private:
    static WeeduLessonRouter *m_pInstance;   
    void selectUIWithDatasourceAndCurrentStep(wetalkevents_t datasource, int currentStep);

signals:

public slots:
};

#endif // WEEDULESSONROUTER_H
