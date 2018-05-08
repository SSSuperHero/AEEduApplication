#include "mesgboxwidhget.h"
#include <QPainter>
#include <QEventLoop>

#pragma execution_character_set("utf-8")
MesgBoxWidhget::MesgBoxWidhget(QWidget *parent) :
    BaseMainWidget(parent),
    m_clickButtonFlag(ECHO_MESSAGEBOX_CANCLE)
{
    resize( 360, 280 );
    reSetSize( this );
    setResizeEnabled( false );

    widgetShowCenter();

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog|Qt::Tool|Qt::X11BypassWindowManagerHint);
    this->setWindowModality(Qt::ApplicationModal);
//    this->setWindowOpacity(0.95);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute( Qt::WA_DeleteOnClose );
    intUI();

}

void MesgBoxWidhget::intUI()
{
    m_p.load(":/images/msgBox_bk.png");

    m_close=new QPushButton(this);
    m_close->setStyleSheet("QPushButton{border-image:url(:/images/widget_clos_1.png);"
                           "background-repeat:no-repeat;}"
                           "QPushButton:hover{border-image:url(:/images/widget_clos_2.png);}");
    connect(m_close,SIGNAL(released()),this,SLOT(closeBox()));

    m_title=new QLabel(this);
    m_title->setAlignment(Qt::AlignCenter);

    m_info=new QLabel(this);
    m_info->setAlignment(Qt::AlignCenter);
    m_info->setWordWrap(true);
    m_info->setStyleSheet("color: #666666;");

    m_ok = new QPushButton(tr("Ok"),this);
    m_ok->setStyleSheet("QPushButton{border-image:url(:/images/msg_ok1.png);"
                        "background-repeat:no-repeat;}"
                        "QPushButton:hover{border-image:url(:/images/msg_ok2.png);}"
                        "QPushButton:press{border-image:url(:/images/msg_ok3.png);}");
    m_ok->setVisible(false);
    QObject::connect(m_ok,SIGNAL(released()),this,SLOT(ok_clicked()));


    m_cancle = new QPushButton(tr("Cancle"),this);
    m_cancle->setStyleSheet("QPushButton{border-image:url(:/images/msg_cancle1.png);color: #ffffff;"
                            "background-repeat:no-repeat;}"
                            "QPushButton:hover{border-image:url(:/images/msg_cancle2.png);}"
                            "QPushButton:press{border-image:url(:/images/msg_cancle3.png);}");
    m_cancle->setVisible(false);
    QObject::connect(m_cancle,SIGNAL(released()),this,SLOT(cancle_clicked()));
}

void MesgBoxWidhget::resizeEvent(QResizeEvent *)
{
    m_close->setGeometry(width()*0.85,height()*0.15,width()*0.04,width()*0.04);

    m_title->setGeometry(width()*0.08,height()*0.12,width()*0.78,height()*0.15);

    m_info->setGeometry(width()*0.08,height()*0.30,width()*0.84,height()*0.40);
}

void MesgBoxWidhget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),m_p);
}

void MesgBoxWidhget::closeBox()
{
    cancle_clicked();
}

void MesgBoxWidhget::set_title(QString str)
{
    m_title->setText(str);
}

void MesgBoxWidhget::set_info(QString str)
{
    m_info->setText(str);
}

void MesgBoxWidhget::set_bellDownLoadInfo( const QString _bellGoldNum, const QString _RMBNum,
                                          const QString _curBellGoldNum, const QString creationInfo )
{
    m_info->hide();

    m_bellText = new QLabel( tr("铃声价格:"), this );
//    m_bellText->setFont(QFont("微软雅黑",8,false));
    reSetFont( QFont("微软雅黑",8,false), m_bellText );
    m_bellText->setStyleSheet("color: #666666;");
    m_bellText->setGeometry( getWidth(100), getHeight(106), getWidth(52), getHeight(20) );

    m_curBellText = new QLabel( tr("当前余额:"), this );
//    m_curBellText->setFont(QFont("微软雅黑",8,false));
    reSetFont( QFont("微软雅黑",8,false), m_curBellText );
    m_curBellText->setStyleSheet("color: #666666;");
    m_curBellText->setGeometry( getWidth(100), getHeight(135), getWidth(52), getHeight(20) );

    m_creationInfo = new QLabel( creationInfo, this );
//    m_creationInfo->setFont(QFont("微软雅黑",8,false));
    reSetFont( QFont("微软雅黑",8,false), m_creationInfo );
    m_creationInfo->setStyleSheet("color:#999999;");
    m_creationInfo->setGeometry( getWidth(90), getHeight(160), getWidth(200), getHeight(20) );

    m_bellGoldNum = new QLabel( _bellGoldNum, this );
//    m_bellGoldNum->setFont(QFont("微软雅黑",9,false));
    reSetFont( QFont("微软雅黑",9,false), m_bellGoldNum );
    m_bellGoldNum->setStyleSheet("color:#333333;");
    m_bellGoldNum->setGeometry( getWidth(180), getHeight(106), getWidth(50), getHeight(20) );

    m_curBellGoldNum = new QLabel( _curBellGoldNum, this );
//    m_curBellGoldNum->setFont(QFont("微软雅黑",9,false));
    reSetFont( QFont("微软雅黑",9,false), m_curBellGoldNum );
    m_curBellGoldNum->setStyleSheet("color:#333333;");
    m_curBellGoldNum->setGeometry( getWidth(180), getHeight(135), getWidth(100), getHeight(20) );

    m_RMBNum = new QLabel( _RMBNum, this );
//    m_RMBNum->setFont(QFont("微软雅黑",7,false));
    reSetFont( QFont("微软雅黑",7,false), m_RMBNum );
    m_RMBNum->setStyleSheet("color: #666666;");
    m_RMBNum->setGeometry( getWidth(223), getHeight(106), getWidth(52), getHeight(20) );

    m_goldPic1 = new ClickedLabel(this);
    m_goldPic1->setPixmap(QPixmap(":/images/globPic.png"));
    m_goldPic1->setGeometry( getWidth(158), getHeight(108), getWidth(16), getHeight(16) );

    m_goldPic2 = new ClickedLabel(this);
    m_goldPic2->setPixmap(QPixmap(":/images/globPic.png"));
    m_goldPic2->setGeometry( getWidth(158), getHeight(137), getWidth(16), getHeight(16) );

}

void MesgBoxWidhget::set_bellMakeInfo()
{
    m_title->hide();
    m_info->hide();
    m_ok->hide();
    m_cancle->hide();
    m_close->hide();

    this->setMinimumSize( getWidth(420), getHeight(320) );
    this->setMaximumSize( getWidth(420), getHeight(320) );

    m_p.load(":/images/bellSave.png");

    m_bellClose = new QPushButton(this);
    m_bellClose->setStyleSheet("QPushButton{border-image:url(:/images/widget_clos_1.png);"
                           "background-repeat:no-repeat;}"
                           "QPushButton:hover{border-image:url(:/images/widget_clos_2.png);}");
    connect(m_bellClose,SIGNAL(released()),this,SLOT(closeBox()));
    m_bellClose->setGeometry( getWidth(372), getHeight(35), getWidth(13), getHeight(13) );

    m_bellDownload = new QPushButton(tr("下载铃声并使用"),this);
    m_bellDownload->setFont(QFont("微软雅黑",8,false));
    reSetFont( QFont("微软雅黑",8,false), m_bellDownload );
    m_bellDownload->setStyleSheet("QPushButton{border-image:url(:/images/msg_cancle1.png);color:#ffffff;"
                                  "background-repeat:no-repeat;}"
                                  "QPushButton:hover{border-image:url(:/images/msg_cancle2.png);}"
                                  "QPushButton:press{border-image:url(:/images/msg_cancle3.png);}");
    m_bellDownload->setGeometry( getWidth(140), getHeight(140), getWidth(140), getHeight(32) );
    connect(m_bellDownload,SIGNAL(clicked(bool)),this,SLOT(downlad_clicked()));

    m_bellManage = new QPushButton(tr("铃声管理"),this);
//    m_bellManage->setFont(QFont("微软雅黑",8,false));
    reSetFont( QFont("微软雅黑",8,false), m_bellManage );
    m_bellManage->setStyleSheet("QPushButton{border-image:url(:/images/msg_ok1.png);color:#666666;"
                                "background-repeat:no-repeat;}"
                                "QPushButton:hover{border-image:url(:/images/msg_ok2.png);}"
                                "QPushButton:press{border-image:url(:/images/msg_ok3.png);}");
    m_bellManage->setGeometry( getWidth(140), getHeight(182), getWidth(140), getHeight(32) );
    connect(m_bellManage,SIGNAL(clicked(bool)),this,SLOT(manage_clicked()));

    m_bellText = new QLabel( "铃声保存成功！", this );
//    m_bellText->setFont(QFont("微软雅黑",9,false));
    reSetFont( QFont("微软雅黑",9,false), m_bellText );
    m_bellText->setStyleSheet("color:#6ed56c;");
    m_bellText->setGeometry( getWidth(175), getHeight(70), getWidth(140), getHeight(20) );

    m_curBellText = new QLabel( "你可以在铃声管理中找到保存的铃声", this );
//    m_curBellText->setFont(QFont("微软雅黑",9,false));
    reSetFont( QFont("微软雅黑",8,false), m_curBellText );
    m_curBellText->setStyleSheet("color: #666666;");
    m_curBellText->setGeometry( getWidth(120), getHeight(96), getWidth(220), getHeight(20) );

    m_goldPic1 = new ClickedLabel(this);
    m_goldPic1->setPixmap(QPixmap(":/images/finished.png"));
    m_goldPic1->setGeometry( getWidth(152), getHeight(70), getWidth(20), getHeight(20) );

    m_goldPic2 = new ClickedLabel( "如何使用铃声？", this );
//    m_goldPic2->setFont(QFont("微软雅黑",8,false));
    reSetFont( QFont("微软雅黑",8,false), m_goldPic2 );
    m_goldPic2->setStyleSheet("QLabel{color:#666666;"
                                 "background-repeat:no-repeat;}"
                                 "QLabel:hover{color:#6ed56c;}");
//    m_goldPic2->setPixmap(QPixmap(":/images/point1.png"));
    m_goldPic2->setGeometry( getWidth(170), getHeight(260), getWidth(80), getHeight(20) );
    connect( m_goldPic2,&ClickedLabel::Clicked,this,&MesgBoxWidhget::slot_clickBellInstructions );

    widgetShowCenter();
}

void MesgBoxWidhget::showBellInstructions()
{
    m_title->hide();
    m_info->hide();
    m_ok->hide();
    m_cancle->hide();
    m_close->hide();
    m_p.load(":/images/alert_background.png");

    this->setMinimumSize( getWidth(500), getHeight(480) );
    this->setMaximumSize( getWidth(500), getHeight(480) );

    m_creationInfo = new QLabel( tr("如何使用铃声"), this );
//    m_creationInfo->setFont(QFont("微软雅黑",9,false));
    reSetFont( QFont("微软雅黑",9,false), m_creationInfo );
    m_creationInfo->setStyleSheet("color:#666666;");
    m_creationInfo->setGeometry( getWidth(200), getHeight(30), getWidth(140), getHeight(30) );

    m_bellClose = new QPushButton(this);
    m_bellClose->setStyleSheet("QPushButton{border-image:url(:/images/widget_clos_1.png);"
                           "background-repeat:no-repeat;}"
                           "QPushButton:hover{border-image:url(:/images/widget_clos_2.png);}");
    connect(m_bellClose,SIGNAL(released()),this,SLOT(closeBox()));
    m_bellClose->setGeometry( getWidth(450), getHeight(35), getWidth(13), getHeight(13) );

    m_bellText = new QLabel( this );
    m_bellText->setGeometry( getWidth(50), getHeight(80), getWidth(395), getHeight(290) );
    m_bellText->setStyleSheet("border-image: url(:/images/bellUseInfo.png);");
//    m_bellText->setPixmap(QPixmap(":/images/bellUseInfo.png"));

    m_bellDownload = new QPushButton(tr("我知道了"),this);
//    m_bellDownload->setFont(QFont("微软雅黑",9,false));
    reSetFont( QFont("微软雅黑",9,false), m_bellDownload );
    m_bellDownload->setStyleSheet("QPushButton{border-image:url(:/images/msg_cancle1.png);color:#ffffff;"
                                  "background-repeat:no-repeat;}"
                                  "QPushButton:hover{border-image:url(:/images/msg_cancle2.png);}"
                                  "QPushButton:press{border-image:url(:/images/msg_cancle3.png);}");
    m_bellDownload->setGeometry( getWidth(175), getHeight(405), getWidth(140), getHeight(32) );
    connect(m_bellDownload,SIGNAL(clicked(bool)),this,SLOT(downlad_clicked()));

    widgetShowCenter();
}

void MesgBoxWidhget::slot_clickBellInstructions()
{
    EchoMessageBox::bellInstructions( this, "如何使用铃声", "我知道了", "", false );
}

void MesgBoxWidhget::set_ok_cancle(bool flag)
{
    if(flag)
    {
        m_ok->setVisible(true);
        m_cancle->setVisible(true);
        m_ok->setGeometry(width()*0.25,height()*0.70,width()*0.2,height()*0.1);
        m_cancle->setGeometry(width()*0.55,height()*0.70,width()*0.2,height()*0.1);
    }
    else
    {
        m_ok->setVisible(true);
        m_cancle->setVisible(false);
        m_ok->setGeometry(width()*0.35,height()*0.68,width()*0.3,height()*0.12);
        m_ok->setStyleSheet("QPushButton{border-image:url(:/images/msg_cancle1.png);color: #ffffff;"
                                "background-repeat:no-repeat;}"
                                "QPushButton:hover{border-image:url(:/images/msg_cancle2.png);}"
                                "QPushButton:press{border-image:url(:/images/msg_cancle3.png);}");
    }
}

void MesgBoxWidhget::set_ok_text(QString str)
{
    m_ok->setText(str);
}

void MesgBoxWidhget::set_cancle_text(QString str)
{
    m_cancle->setText(str);
}

void MesgBoxWidhget::ok_clicked()
{
    m_clickButtonFlag = ECHO_MESSAGEBOX_OK;
    emit signal_clickButton( m_clickButtonFlag );

    this->close();
}

void MesgBoxWidhget::cancle_clicked()
{
    m_clickButtonFlag = ECHO_MESSAGEBOX_CANCLE;
    emit signal_clickButton( m_clickButtonFlag );

    this->close();
}

void MesgBoxWidhget::downlad_clicked()
{
    m_clickButtonFlag = ECHO_MESSAGEBOX_DOWNLOAD;
    emit signal_clickButton( m_clickButtonFlag );

    this->close();
}

void MesgBoxWidhget::manage_clicked()
{
    m_clickButtonFlag = ECHO_MESSAGEBOX_OTHER;
    emit signal_clickButton( m_clickButtonFlag );

    this->close();
}

ECHO_MESSAGEBOX_RETURN MesgBoxWidhget::returnClickFlag()
{
    QEventLoop eventLoop;
    eventLoop.connect( this, SIGNAL(signal_clickButton(bool)), &eventLoop, SLOT( quit() ) );
    eventLoop.exec( QEventLoop::DialogExec );

    return m_clickButtonFlag;
}

ECHO_MESSAGEBOX_RETURN EchoMessageBox::information(QWidget *parent, const QString &title,
      const QString &text, const QString OkText, const QString cancleText, const bool cancleFlag )
{
    MesgBoxWidhget *box = new MesgBoxWidhget( parent );
    box->set_title( title );
    box->set_info( text );
    box->set_ok_text( OkText );
    box->set_cancle_text( cancleText );
    box->set_ok_cancle( cancleFlag );
    box->show();

    return box->returnClickFlag();
}

ECHO_MESSAGEBOX_RETURN EchoMessageBox::bellGoldInfo(QWidget *parent, const QString &title,
                                                    const QString _bellGoldNum, const QString _RMBNum,
                                                    const QString _curBellGoldNum, const QString creationInfo,
                                                    const QString OkText, const QString cancleText, const bool cancleFlag )
{
    MesgBoxWidhget *box = new MesgBoxWidhget( parent );
    box->set_title( title );
    box->set_bellDownLoadInfo( _bellGoldNum, _RMBNum, _curBellGoldNum, creationInfo );
    box->set_ok_text( OkText );
    box->set_cancle_text( cancleText );
    box->set_ok_cancle( cancleFlag );
    box->show();

    return box->returnClickFlag();
}

ECHO_MESSAGEBOX_RETURN EchoMessageBox::bellMakeInfo(QWidget *parent, const QString &title,
                                                    const QString OkText, const QString cancleText,
                                                    const bool cancleFlag )
{
    MesgBoxWidhget *box = new MesgBoxWidhget( parent );
    box->set_title( title );
    box->set_ok_text( OkText );
    box->set_cancle_text( cancleText );
    box->set_ok_cancle( cancleFlag );
    box->set_bellMakeInfo();
    box->show();

    return box->returnClickFlag();
}

ECHO_MESSAGEBOX_RETURN EchoMessageBox::bellInstructions(QWidget *parent, const QString &title,
                                                    const QString OkText, const QString cancleText,
                                                    const bool cancleFlag )
{
    MesgBoxWidhget *box = new MesgBoxWidhget( parent );
    box->set_title( title );
    box->set_ok_text( OkText );
    box->set_cancle_text( cancleText );
    box->set_ok_cancle( cancleFlag );
    box->showBellInstructions();
    box->show();

    return box->returnClickFlag();
}
