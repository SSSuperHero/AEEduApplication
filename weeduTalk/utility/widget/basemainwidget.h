#ifndef BASEMAINWIDGET_H
#define BASEMAINWIDGET_H

#include "frameless.h"
#include <QFrame>
#include <QSystemTrayIcon>
#include <QListWidget>
#include "basewidget.h"

class BaseMainWidget : public BaseWidget
{
    Q_OBJECT
public:
    explicit BaseMainWidget(QWidget *parent = 0);
    ~BaseMainWidget();
    void setResizeEnabled(bool value);

    void setRoundedEnabled(const int &_roundNum, bool flag = true);

//    QSize reSetSize(QWidget *_widget , bool _isSetMax = true);
signals:
    void signal_close();

public slots:

protected:
    void closeEvent(QCloseEvent* /*event*/);
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);
private:
    FrameLess *frameless;

    bool RoundedFlag;
    int RoundedNum;
};

#endif // BASEMAINWIDGET_H
