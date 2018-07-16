#include "weeducoursemainwidget.h"
#include "ui_weeducoursemainwidget.h"
#include <QDebug>
#include <QTimer>

WeeduCourseMainWidget::WeeduCourseMainWidget(QWidget *parent) :
    BaseMainWidget(parent),
    ui(new Ui::WeeduCourseMainWidget),
    m_crrentOperateNum(0)
{
    ui->setupUi(this);

    init();
}

void WeeduCourseMainWidget::init()
{
    m_bottomControlWidget = new BottomControlWidget( this );
    ui->horizontalLayout_bottom->addWidget( m_bottomControlWidget );
    connect( m_bottomControlWidget, &BottomControlWidget::signal_playNext,
             this, &WeeduCourseMainWidget::slot_playNext );
    connect( m_bottomControlWidget, &BottomControlWidget::signal_playPrev,
             this, &WeeduCourseMainWidget::slot_playPrev );
//    connect( m_bottomControlWidget, &BottomControlWidget::signal_palyPause,
//             this, &WeeduCourseMainWidget::slot_palyPause );

    m_headControlWidget = new HeadControlWidget( this );
    ui->verticalLayout_head->addWidget( m_headControlWidget );

    m_topControlWidget = new TopControlWidget( this );
    ui->verticalLayout_head->addWidget( m_topControlWidget );
    connect( m_topControlWidget, &TopControlWidget::signal_back,
             this, &WeeduCourseMainWidget::signal_currentCourseFinish );

}

void WeeduCourseMainWidget::addWidget( QWidget *_courseShowWidget )
{
//    if( ui->horizontalLayout->count() > 0 )
//        clearLayout( ui->horizontalLayout );

    ui->horizontalLayout->addWidget( _courseShowWidget );
}

void WeeduCourseMainWidget::slot_chooseFinish()
{
    QTimer::singleShot( 2*1000, this, &WeeduCourseMainWidget::slot_playNext );
}

void WeeduCourseMainWidget::slot_playNext()
{

    emit signal_currentOperateFinish( m_crrentOperateNum + 1 );

    qDebug()<<" WeeduCourseMainWidget m_crrentOperateNum:"<<m_crrentOperateNum;
}

void WeeduCourseMainWidget::slot_playPrev()
{

    m_crrentOperateNum -= 1;
    if( m_crrentOperateNum < 0 )
    {
        emit signal_currentCourseFinish();
    }
    else
    {
        emit signal_currentOperateFinish( m_crrentOperateNum );
    }


    qDebug()<<" WeeduCourseMainWidget m_crrentOperateNum:"<<m_crrentOperateNum;
}

void WeeduCourseMainWidget::slot_palyPause()
{

}

WeeduCourseMainWidget::~WeeduCourseMainWidget()
{
    delete ui;
}
