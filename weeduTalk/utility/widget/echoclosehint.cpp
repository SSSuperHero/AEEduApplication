#include "echoclosehint.h"
#include "ui_echoclosehint.h"

EchoCloseHint::EchoCloseHint(QWidget *parent) :
    BaseMainWidget(parent),
    ui(new Ui::EchoCloseHint),
    m_isHintFlag( false )
{
    ui->setupUi(this);
    reSetSize( this );
    setResizeEnabled( false );

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog|Qt::Tool|Qt::X11BypassWindowManagerHint);
    this->setWindowModality(Qt::ApplicationModal);
    this->setAttribute(Qt::WA_TranslucentBackground);
    initUi();

    this->setAttribute( Qt::WA_DeleteOnClose );
}

EchoCloseHint::~EchoCloseHint()
{
    delete ui;
}

void EchoCloseHint::initUi()
{
    reSetSize( ui->labelTitle );
    reSetSize( ui->pushButtonClose );
    reSetSize( ui->pushButton );
    reSetSize( ui->widget );
    reSetSize( ui->widgetTittle );
    reSetSize( ui->radioButtonClose );
    reSetSize( ui->radioButtonHide );
    reSetSize( ui->label );

    ui->horizontalLayout_button->setContentsMargins( getWidth(30),getHeight(0),
                                                     getWidth(30),getHeight(0) );
    ui->verticalLayout_back->setContentsMargins( getWidth(33),getHeight(35),
                                                     getWidth(33),getHeight(35) );
    ui->verticalLayout_msg->setContentsMargins( getWidth(40),getHeight(0),
                                                     getWidth(30),getHeight(0) );
    ui->verticalLayout_msg->setSpacing( getHeight(12) );
}

void EchoCloseHint::on_pushButtonClose_clicked()
{
    m_clickButtonType = CLOSE_TYPE_NONE;
    signal_clickCloseType( m_clickButtonType );
    close();
}

void EchoCloseHint::on_pushButton_clicked()
{
    if( ui->radioButtonHide->isChecked() )
    {
        m_clickButtonType = CLOSE_TYPE_HIDE;
    }
    else
        m_clickButtonType = CLOSE_TYPE_CLOSE;

    if( ui->checkBox->checkState() == Qt::Checked )
        m_isHintFlag = true;
    else
        m_isHintFlag = false;

    signal_clickCloseType( m_clickButtonType );
    close();
}

ECHO_CLOSE_TYPE EchoCloseHint::getClickType( bool &_isHintFlag )
{
    QEventLoop eventLoop;
    eventLoop.connect( this, SIGNAL(signal_clickCloseType(ECHO_CLOSE_TYPE)),
                       &eventLoop, SLOT( quit() ) );
    eventLoop.exec( QEventLoop::DialogExec );

    _isHintFlag = m_isHintFlag;
    return m_clickButtonType;
}
