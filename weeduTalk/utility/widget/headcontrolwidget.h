#ifndef HEADCONTROLWIDGET_H
#define HEADCONTROLWIDGET_H

#include <QWidget>
#include "utility/widget/basewidget.h"

namespace Ui {
class HeadControlWidget;
}

class HeadControlWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit HeadControlWidget(QWidget *parent = 0);
    ~HeadControlWidget();

public:
signals:
    void signal_widgetClose();
    void signal_widgetMax();
    void signal_widgetMin();

private slots:
    void on_pushButtonMin_clicked();

    void on_pushButton_max_clicked();

    void on_pushButton_close_clicked();

private:
    Ui::HeadControlWidget *ui;
};

#endif // HEADCONTROLWIDGET_H
