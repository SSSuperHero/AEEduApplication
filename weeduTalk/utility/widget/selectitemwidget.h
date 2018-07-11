#ifndef SELECTITEMWIDGET_H
#define SELECTITEMWIDGET_H

#include <QWidget>
#include "weedulessonguidewidget.h"

namespace Ui {
class SelectItemWidget;
}

class SelectItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectItemWidget(QWidget *parent = 0);

    void bindData(const QString _titleStr, const wetalkDataListItem _data );

    ~SelectItemWidget();

protected:
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::SelectItemWidget            *ui;

    wetalkDataListItem              m_dataInfo;
};

#endif // SELECTITEMWIDGET_H
