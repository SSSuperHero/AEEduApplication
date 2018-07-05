#ifndef SELECTITEMWIDGET_H
#define SELECTITEMWIDGET_H

#include <QWidget>

namespace Ui {
class SelectItemWidget;
}

class SelectItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectItemWidget(QWidget *parent = 0);
    ~SelectItemWidget();

private:
    Ui::SelectItemWidget *ui;
};

#endif // SELECTITEMWIDGET_H
