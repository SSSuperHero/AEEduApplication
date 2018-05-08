#ifndef ECHOCLOSEHINT_H
#define ECHOCLOSEHINT_H

#include <QWidget>
#include "utility/widget/basemainwidget.h"

namespace Ui {
class EchoCloseHint;
}

enum ECHO_CLOSE_TYPE
{
    CLOSE_TYPE_NONE = 0,
    CLOSE_TYPE_HIDE,
    CLOSE_TYPE_CLOSE
};

class EchoCloseHint : public BaseMainWidget
{
    Q_OBJECT

public:
    explicit EchoCloseHint(QWidget *parent = 0);
    ~EchoCloseHint();

private slots:
    void on_pushButtonClose_clicked();

    void on_pushButton_clicked();

public:
    ECHO_CLOSE_TYPE getClickType(bool &_isHintFlag);
signals:
    void signal_clickCloseType( const ECHO_CLOSE_TYPE );
private:
    void initUi();

private:
    Ui::EchoCloseHint *ui;

    ECHO_CLOSE_TYPE m_clickButtonType;
    bool            m_isHintFlag;
};

#endif // ECHOCLOSEHINT_H
