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
//    static WeeduLessonRouter* GetInstance()
//    {
//        if(m_pInstance == NULL)
//        {
//            m_pInstance = new WeeduLessonRouter();
//        }
//        return m_pInstance;
//    }

//    static void Release()
//    {
//        if(m_pInstance != NULL)
//        {
//            delete m_pInstance;
//            m_pInstance = NULL;
//        }
//    }

    void showRouterWithClassInfoAndWidget(wetalkgetClassInfo _classInfo, QWidget *_widget);

private:
    static WeeduLessonRouter *m_pInstance;


signals:

public slots:
};

#endif // WEEDULESSONROUTER_H
