#ifndef CLICKLABEL_H
#define CLICKLABEL_H
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
class ClickedLabel : public QLabel
{
    Q_OBJECT

public:
    ClickedLabel(QString str,QWidget *parent=0);
    ClickedLabel(QWidget *parent=0);

    void setInfoId(const int _infoId);
    int getInfoId();
signals:
    void Clicked(ClickedLabel* clicked);
protected:
    void paintEvent(QPaintEvent *e);
private:
    void mouseReleaseEvent( QMouseEvent* );

private:
    int     m_infoId;
};

#endif // CLICKLABEL_H
