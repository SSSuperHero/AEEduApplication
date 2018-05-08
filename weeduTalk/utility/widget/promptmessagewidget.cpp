#include "promptmessagewidget.h"
#include "ui_promptmessagewidget.h"
#include <QTimer>

promptMessageWidget::promptMessageWidget(int showSecondNum, QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::promptMessageWidget)
{
    ui->setupUi(this);

    setWindowFlags( Qt::FramelessWindowHint | Qt::Tool );
    setAttribute( Qt::WA_TranslucentBackground, true );
    setAttribute(Qt::WA_DeleteOnClose);

    QTimer::singleShot( showSecondNum*1000,this,&promptMessageWidget::close );

}

void promptMessageWidget::setPromptMessage(QString promptMessage)
{
    QString strElidedText = ui->label->fontMetrics().elidedText(promptMessage,
                                                             Qt::ElideRight, 200, Qt::TextShowMnemonic);
    ui->label->setText(promptMessage);
}

void promptMessageWidget::setImage( QString _img )
{
    QString _style = QString( "background-color: rgba(255, 255, 255,0);");
    ui->label->setStyleSheet( _style );

    ui->label->setPixmap(QPixmap(_img).scaled(this->width(),this->height()));
}

void promptMessageWidget::ShowMsg(const QString &msgContent, QWidget *parent, int showSecondNum)
{
    promptMessageWidget *messagewidget = new promptMessageWidget( showSecondNum, parent );
    messagewidget->reSetSize( messagewidget );
    messagewidget->setPromptMessage(msgContent);

    messagewidget->widgetShowCenter();
    messagewidget->show();
}

void promptMessageWidget::ShowImg(const QString &_img, QWidget *parent,
                                  int showSecondNum , QPoint _point)
{
    promptMessageWidget *messagewidget = new promptMessageWidget( showSecondNum, parent );
    messagewidget->resize( PROMPT_WND_WIDTH, PROMPT_WND_HEIGHT );
    messagewidget->reSetSize( messagewidget );
    messagewidget->setImage( _img );

    messagewidget->move( _point );
    messagewidget->show();
}

promptMessageWidget::~promptMessageWidget()
{
    delete ui;
}
