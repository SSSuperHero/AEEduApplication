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

    void setDataInfo(const int _infoId, const int _totleIndex, const int _curIndex );
    int getInfoId();
    int getTotleIndex();
    int getCurrentIndex();
signals:
    void Clicked(ClickedLabel* clicked);
protected:
    void paintEvent(QPaintEvent *e);
private:
    void mouseReleaseEvent( QMouseEvent* );

private:
    int     m_infoId;
    int     m_totleIndex;
    int     m_curIndex;
};

#endif // CLICKLABEL_H
