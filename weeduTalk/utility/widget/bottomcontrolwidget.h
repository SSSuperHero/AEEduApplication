#ifndef BOTTOMCONTROLWIDGET_H
#define BOTTOMCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class BottomControlWidget;
}

class BottomControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BottomControlWidget(QWidget *parent = 0);
    ~BottomControlWidget();

public:
signals:
    void signal_palyPause();
    void signal_playPrev();
    void signal_playNext();
    void signal_sr();
    void signal_playRepeat();
    void signal_listen();

private:
    Ui::BottomControlWidget *ui;
};

#endif // BOTTOMCONTROLWIDGET_H
