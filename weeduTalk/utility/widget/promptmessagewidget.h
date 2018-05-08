#ifndef PROMPTMESSAGEWIDGET_H
#define PROMPTMESSAGEWIDGET_H

#include <QWidget>
#include "basewidget.h"

namespace Ui {
class promptMessageWidget;
}

class promptMessageWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit promptMessageWidget( int showSecondNum, QWidget *parent = 0 );
    ~promptMessageWidget();

public:
    void setPromptMessage(QString promptMessage);
    static void ShowMsg(const QString& msgContent, QWidget *parent = 0, int showSecondNum = 2);

    void setImage(QString _img);
    static void ShowImg(const QString &_img, QWidget *parent, int showSecondNum, QPoint _point );
private:
    Ui::promptMessageWidget *ui;
};

#endif // PROMPTMESSAGEWIDGET_H
