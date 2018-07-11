#include "weeducomprehensionwidget.h"
#include "ui_weeducomprehensionwidget.h"
#include "utility/widget/selectitemwidget.h"
#include <QDebug>

WeeduComprehensionWidget::WeeduComprehensionWidget(QWidget *parent) :
    WeeduCourseWidgetBase(parent),
    ui(new Ui::WeeduComprehensionWidget),
    m_crrentOperateNum(0)
{
    ui->setupUi(this);

    init();
}

void WeeduComprehensionWidget::init()
{
    m_bottomControlWidget = new BottomControlWidget( this );
    ui->horizontalLayout_bottom->addWidget( m_bottomControlWidget );
    connect( m_bottomControlWidget, &BottomControlWidget::signal_playNext,
             this, &WeeduComprehensionWidget::slot_playNext );

    m_headControlWidget = new HeadControlWidget( this );
    ui->verticalLayout_head->addWidget( m_headControlWidget );

    m_topControlWidget = new TopControlWidget( this );
    ui->verticalLayout_head->addWidget( m_topControlWidget );
}

void WeeduComprehensionWidget::loadData( const wetalkevents _dataInfo, const int _currentOperateNum )
{
    m_operateDataInfo = _dataInfo;
    m_crrentOperateNum = _currentOperateNum;

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

void WeeduComprehensionWidget::slot_playNext()
{
    emit signal_currentOperateFinish( m_crrentOperateNum + 1 );
}

WeeduComprehensionWidget::~WeeduComprehensionWidget()
{
    delete ui;
}
