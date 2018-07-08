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
    void on_pushButtonPause_clicked();
    void on_pushButtonPrev_clicked();
    void on_pushButtonNext_clicked();
    void on_pushButtonAgain_clicked();
    void on_pushButtonSpeak_clicked();
    void on_pushButtonListen_clicked();


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
