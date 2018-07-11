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

signals:
    void signal_currentOperateFinish( const int _nextOperateNum );
public slots:
};

#endif // WEEDUCOURSEWIDGETBASE_H
