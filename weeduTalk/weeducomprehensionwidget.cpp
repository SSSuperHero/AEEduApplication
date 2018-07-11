#include "weeducomprehensionwidget.h"
#include "ui_weeducomprehensionwidget.h"
#include "utility/widget/selectitemwidget.h"
#include <QDebug>

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

void WeeduComprehensionWidget::initDataInfo( const wetalkevents _dataInfo )
{
    m_operateDataInfo = _dataInfo;

    qDebug()<<"WeeduComprehensionWidget initDataInfo size:"<< m_operateDataInfo.multipleChoicesList.at(0).items.size()<<m_operateDataInfo.num;
    if( m_operateDataInfo.multipleChoicesList.at(0).items.size() > 0 )
    {
        foreach (wetalkDataListItem _itemData, m_operateDataInfo.multipleChoicesList.at(0).items)
        {
            SelectItemWidget *_selectItem = new SelectItemWidget(this);
            _selectItem->bindData( "A", _itemData );
            ui->verticalLayout->addWidget( _selectItem );
        }
    }
}

WeeduComprehensionWidget::~WeeduComprehensionWidget()
{
    delete ui;
}
