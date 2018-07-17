#ifndef WEEDUCOURSEWIDGETBASE_H
#define WEEDUCOURSEWIDGETBASE_H

#include <QWidget>
#include "basemainwidget.h"
#include "weedulessonguidewidget.h"

class WeeduCourseWidgetBase : public BaseMainWidget
{
    Q_OBJECT
public:
    explicit WeeduCourseWidgetBase(QWidget *parent = nullptr);

    virtual void loadData( const wetalkevents _dataInfo, const int _currentOperateNum );

public:
    void stopPlayMedia();

public slots:

public:
    int                                 m_currentOperateNum;
    QWidget                             *m_videoWidget;
};

#endif // WEEDUCOURSEWIDGETBASE_H
