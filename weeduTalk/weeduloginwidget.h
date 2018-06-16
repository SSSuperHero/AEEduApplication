#ifndef WEEDULOGINWIDGET_H
#define WEEDULOGINWIDGET_H

#include <QWidget>
#include "utility/widget/basemainwidget.h"
#include "mgr/http/echowebhttpapi.h"
#include "utility/jsonutil.h"
#include "config/configutil.h"

namespace Ui {
class WeeduLoginWidget;
}

namespace  {
    const QString KEY_LOGIN_INFO  = "weeduLogin/info";
}


struct LoginInfo
{
    QString username; //mobile;
    QString password;
    int     shouldRememberPassword;
    int     shouldAutoLogin;
};
BEGIN_TO_JSON(LoginInfo)
MEMBER_TO_JSON(username)
MEMBER_TO_JSON(password)
MEMBER_TO_JSON(shouldRememberPassword)
MEMBER_TO_JSON(shouldAutoLogin)
END_TO_JSON()


BEGIN_FROM_JSON(LoginInfo)
MEMBER_FROM_JSON(username)
MEMBER_FROM_JSON(password)
MEMBER_FROM_JSON(shouldRememberPassword)
MEMBER_FROM_JSON(shouldAutoLogin)
END_FROM_JSON()


class WeeduLoginWidget : public BaseMainWidget
{
    Q_OBJECT

public:
    explicit WeeduLoginWidget(QWidget *parent = 0);
    void init();

    ~WeeduLoginWidget();

private:
    void writeLoginInfo();
    void readLoginInfo();

private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonLogin_clicked();
    void slot_textChanged(const QString &);

    void slot_onWebLoginStart();
    void slot_onWebLoginFinish();
    void slot_onWebLoginSuccess(const QString& response);
    void slot_onWebLoginFailure(const QString& response);

public:
signals:
    void signal_loginSuccess();

private:
    Ui::WeeduLoginWidget *ui;

    EntityNetworkReplyHolder    *loginReply;

};

#endif // WEEDULOGINWIDGET_H
