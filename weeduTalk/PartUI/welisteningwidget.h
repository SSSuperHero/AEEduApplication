#ifndef WELISTENINGWIDGET_H
#define WELISTENINGWIDGET_H

#include <QWidget>
#include <weedulessonguidewidget.h>
#include <utility/widget/bottomcontrolwidget.h>
#include <utility/widget/headcontrolwidget.h>
#include <utility/widget/topcontrolwidget.h>

namespace Ui {
class WeListeningWidget;
}

class WeListeningWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WeListeningWidget(QWidget *parent = 0);
    ~WeListeningWidget();
    void renderWithEventInfo(wetalkevents eventInfo);

private slots:
    void on_showContentButton_clicked();

private:
    Ui::WeListeningWidget *ui;
    void init();
    BottomControlWidget *m_bottomControlWidget;
    HeadControlWidget  *m_headControlWidget;
    TopControlWidget  *m_topControlWidget;
};

#endif // WELISTENINGWIDGET_H
