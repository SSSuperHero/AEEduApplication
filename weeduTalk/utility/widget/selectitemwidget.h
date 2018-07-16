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
    void bindData(const QString _titleStr, const wetalkselectEventItem _data );

    ~SelectItemWidget();

signals:
    void signal_selectFinish();

protected:
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::SelectItemWidget            *ui;

    wetalkDataListItem              m_dataItemInfo;
    wetalkselectEventItem           m_dataSelectItemInfo;
};

#endif // SELECTITEMWIDGET_H
