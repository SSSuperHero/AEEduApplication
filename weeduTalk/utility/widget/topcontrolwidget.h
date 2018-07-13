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
    void setShowText( const QString _text );

signals:
    void signal_back();
    void signal_courseNum( const int num );
    void signal_playRepeatAndShowText();

private slots:
    void on_pushButton_clicked();

    void on_pushButtonText_clicked();

private:
    Ui::TopControlWidget *ui;
};

#endif // TOPCONTROLWIDGET_H
