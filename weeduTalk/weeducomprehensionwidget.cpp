#include "weeducomprehensionwidget.h"
#include "ui_weeducomprehensionwidget.h"

WeeduComprehensionWidget::WeeduComprehensionWidget(QWidget *parent) :
    BaseMainWidget(parent),
    ui(new Ui::WeeduComprehensionWidget)
{
    ui->setupUi(this);

    init();
}

void WeeduComprehensionWidget::init()
{
    m_bottomControlWidget = new BottomControlWidget( this );
    ui->horizontalLayout_bottom->addWidget( m_bottomControlWidget );

    m_headControlWidget = new HeadControlWidget( this );
    ui->verticalLayout_head->addWidget( m_headControlWidget );

    m_topControlWidget = new TopControlWidget( this );
    ui->verticalLayout_head->addWidget( m_topControlWidget );
}

WeeduComprehensionWidget::~WeeduComprehensionWidget()
{
    delete ui;
}
