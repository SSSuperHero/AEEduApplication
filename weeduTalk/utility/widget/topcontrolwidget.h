#ifndef TOPCONTROLWIDGET_H
#define TOPCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class TopControlWidget;
}

class TopControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TopControlWidget(QWidget *parent = 0);
    ~TopControlWidget();

public:
signals:
    void signal_back();
    void signal_courseNum( const int num );
    void signal_playRepeatAndShowText();

private:
    Ui::TopControlWidget *ui;
};

#endif // TOPCONTROLWIDGET_H
