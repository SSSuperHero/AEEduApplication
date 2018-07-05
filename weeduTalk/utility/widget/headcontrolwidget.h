#ifndef HEADCONTROLWIDGET_H
#define HEADCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class HeadControlWidget;
}

class HeadControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeadControlWidget(QWidget *parent = 0);
    ~HeadControlWidget();

public:
signals:
    void signal_close();
    void signal_max();
    void signal_min();

private:
    Ui::HeadControlWidget *ui;
};

#endif // HEADCONTROLWIDGET_H
