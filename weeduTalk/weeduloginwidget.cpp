#include "weeduloginwidget.h"
#include "ui_weeduloginwidget.h"
#include "utility/userinfo.h"

WeeduLoginWidget::WeeduLoginWidget(QWidget *parent) :
    BaseMainWidget(parent),
    ui(new Ui::WeeduLoginWidget)
{
    ui->setupUi(this);

    init();
}

void WeeduLoginWidget::init()
{
    connect( ui->lineEditAccount, &QLineEdit::textChanged, this, &WeeduLoginWidget::slot_textChanged );
    connect( ui->lineEditPassword, &QLineEdit::textChanged, this, &WeeduLoginWidget::slot_textChanged );

    readLoginInfo();
}

WeeduLoginWidget::~WeeduLoginWidget()
{
    delete ui;
}

void WeeduLoginWidget::on_pushButtonClose_clicked()
{
    close();
}

void WeeduLoginWidget::on_pushButtonLogin_clicked()
{
    QString userName = ui->lineEditAccount->text();
    QString password = ui->lineEditPassword->text();

    loginReply = EchoWebHttpApi::instance()->login(this, userName, password);

    connect(loginReply, &EntityNetworkReplyHolder::signal_onStart,
            this, &WeeduLoginWidget::slot_onWebLoginStart);
    connect(loginReply, &EntityNetworkReplyHolder::signal_onFinish,
            this, &WeeduLoginWidget::slot_onWebLoginFinish);
    connect(loginReply, &EntityNetworkReplyHolder::signal_onSuccess,
            this, &WeeduLoginWidget::slot_onWebLoginSuccess);
    connect(loginReply, &EntityNetworkReplyHolder::signal_onError,
            this, &WeeduLoginWidget::slot_onWebLoginFailure);
}

void WeeduLoginWidget::slot_onWebLoginStart()
{
    ui->pushButtonRegister->setEnabled( false );
    ui->pushButtonLogin->setEnabled( false );

}

void WeeduLoginWidget::slot_onWebLoginFinish()
{

}

void WeeduLoginWidget::slot_onWebLoginSuccess(const QString &response)
{
    qInfo()<<"slot_onWebLoginSuccess response:"<<response;

    HttpEntity<loginDetailsInfoEntity> loginDetailsInfo;
    fromJson( response, loginDetailsInfo );

    userInfoMgr::instance()->setUserInfo( loginDetailsInfo.data );
    userInfoMgr::instance()->setToken( loginDetailsInfo.data.access_token );

    writeLoginInfo();

    emit signal_loginSuccess();

}

void WeeduLoginWidget::slot_onWebLoginFailure(const QString& response)
{
    qInfo()<<"slot_onWebLoginFailure response:"<<response;

//    HttpEntity<loginDetailsInfoEntity> loginDetailsInfo;
//    fromJson( response, loginDetailsInfo );

//    loginFinish( loginDetailsInfo.message );

}

void WeeduLoginWidget::writeLoginInfo()
{
    qInfo("writeLoginInfo");

    LoginInfo loginInfo;
    loginInfo.username = ui->lineEditAccount->text().trimmed();
    loginInfo.password = ui->lineEditPassword->text().trimmed();

    //use bool instead of int
    loginInfo.shouldAutoLogin = 0;
    loginInfo.shouldRememberPassword = (ui->checkBoxRemember->checkState() == Qt::Checked) ? 1: 0;

    QString jsonLoginInfo = toJson(loginInfo);
    ConfigUtil::setValue(KEY_LOGIN_INFO, jsonLoginInfo);
}

void WeeduLoginWidget::readLoginInfo()
{
    qInfo("readLoginInfo");
    QString jsonLoginInfo = ConfigUtil::value(KEY_LOGIN_INFO, "").toString();
    if (jsonLoginInfo.isEmpty())
    {
        qWarning("no jsonLoginInfo");
        return;
    }

    LoginInfo loginInfo;
    fromJson(jsonLoginInfo, loginInfo);

    ui->lineEditAccount->setText(loginInfo.username);
    ui->checkBoxRemember->setChecked(loginInfo.shouldRememberPassword == 1);
//    ui->chkAutoLogin->setChecked(loginInfo.shouldAutoLogin == 1);

    if (loginInfo.shouldRememberPassword == 1)
    {
        ui->lineEditPassword->setText(loginInfo.password);

//        if( m_shouldAutoLogin )
//            QTimer::singleShot(1*1000, this, &EchoLoginWidget::on_pushButtonLogin_clicked );
    }

}


void WeeduLoginWidget::slot_textChanged(const QString &)
{
    QString userName = ui->lineEditAccount->text();
    QString password = ui->lineEditPassword->text();

    if( userName.isEmpty() || password.isEmpty() )
    {
        ui->pushButtonLogin->setStyleSheet("border-image: url(:/images/btn_unLogin.png);");
        ui->pushButtonLogin->setEnabled(false);
    }
    else
    {
        ui->pushButtonLogin->setStyleSheet("border-image: url(:/images/btn_login.png);");
        ui->pushButtonLogin->setEnabled(true);
    }
}
