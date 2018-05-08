#ifndef WINDGETLABEL_H
#define WINDGETLABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QVariant>
#include "utility/widget/basewidget.h"

enum SEARCH_MUSIC_TYPE
{
    SEARCH_MUSIC_SOUND,
    SEARCH_MUSIC_CHANNEL,
    SEARCH_MUSIC_VIDEO,
    SEARCH_MUSIC_BELL
};

class windgetLabel : public BaseWidget
{
    Q_OBJECT
public:
    explicit windgetLabel(QWidget *parent = 0);
    ~windgetLabel();
signals:
    void signal_searchItem( QVariant, SEARCH_MUSIC_TYPE );
    void signal_doubleClickItem();
    void signal_clickWidgetItem();
public:
    void setBindData(const QString &, const QVariant &, const SEARCH_MUSIC_TYPE &_searchType );
    void set_label_str(const QString &);
private:
    void initUI();
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QLabel* m_label;
    QVariant m_var;
    QString m_str;
    SEARCH_MUSIC_TYPE m_searchType;
};

#endif // WINDGETLABEL_H
