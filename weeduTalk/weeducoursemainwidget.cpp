#include "weeducoursemainwidget.h"
#include "ui_weeducoursemainwidget.h"
#include "utility/widget/weeducoursewidgetbase.h"
#include <PartUI/welisteningwidget.h>
#include "weeducomprehensionwidget.h"
#include "mgr/media/mediaplaymanager.h"
#include <QDebug>
#include <QTimer>

WeeduCourseMainWidget::WeeduCourseMainWidget(QWidget *parent) :
    BaseMainWidget(parent),
    ui(new Ui::WeeduCourseMainWidget),
    m_currentOperateNum(0),
    m_currentOperateWidget(NULL)
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
    connect( m_bottomControlWidget, &BottomControlWidget::signal_palyPause,
             this, &WeeduCourseMainWidget::slot_palyPause );

    m_headControlWidget = new HeadControlWidget( this );
    ui->verticalLayout_head->addWidget( m_headControlWidget );

    m_topControlWidget = new TopControlWidget( this );
    ui->verticalLayout_head->addWidget( m_topControlWidget );
    connect( m_topControlWidget, &TopControlWidget::signal_back,
             this, &WeeduCourseMainWidget::slot_currentCourseFinish );

}

void WeeduCourseMainWidget::selectUIWithDatasourceAndCurrentStep(wetalkevents_t datasource, int currentStep)
{
    if( datasource.size() <= currentStep )
        return;

    this->show();

    m_currentOperateData = datasource;

    wetalkevents eventInfo = datasource.at(currentStep);
    if (eventInfo.type == "passage_listening") {
        m_currentOperateWidget =  new WeListeningWidget;
        m_currentOperateWidget->loadData(eventInfo,currentStep);
//        m_currentOperateWidget->show();

    } else if (eventInfo.type == "passage_comprehension") {
        m_currentOperateWidget =  new WeeduComprehensionWidget;
        m_currentOperateWidget->loadData(eventInfo,currentStep);

    } else if (eventInfo.type.contains("multipleChoices",Qt::CaseSensitive)) {
        m_currentOperateWidget =  new WeeduComprehensionWidget;
        m_currentOperateWidget->loadData(eventInfo,currentStep);

    } else if (eventInfo.type == "dialog_listening") {

    } else if (eventInfo.type == "dialog_comprehension") {

    } else if (eventInfo.type == "dialog_interaction") {

    } else if (eventInfo.type == "") {

    } else if (eventInfo.type == "") {

    } else if (eventInfo.type == "") {

    } else if (eventInfo.type == "") {

    } else if (eventInfo.type == "") {

    } else if (eventInfo.type == "") {

    } else if (eventInfo.type == "") {

    } else if (eventInfo.type == "") {

    } else {

    }

    if( m_currentOperateWidget )
    {
        this->addWidget( m_currentOperateWidget );
    }

}

void WeeduCourseMainWidget::nextOperate( const int _operateNum )
{
    qDebug()<<" m_currentOperateData size:"<<m_currentOperateData.size();
    qDebug()<<" m_currentOperateData _operateNum:"<<_operateNum;

    m_currentOperateWidget->stopPlayMedia();

    if( m_currentOperateData.size() <= _operateNum )
    {
        emit signal_currentCourseFinish();
        return;
    }

    selectUIWithDatasourceAndCurrentStep( m_currentOperateData, _operateNum );
}

void WeeduCourseMainWidget::addWidget( QWidget *_courseShowWidget )
{
    if( ui->horizontalLayout->count() > 0 )
        clearLayout( ui->horizontalLayout );

    if( !_courseShowWidget )
        return;

    ui->horizontalLayout->addWidget( _courseShowWidget );
}

void WeeduCourseMainWidget::slot_chooseFinish()
{

}

void WeeduCourseMainWidget::slot_playNext()
{

    m_currentOperateNum += 1;
    nextOperate( m_currentOperateNum );

    qDebug()<<" WeeduCourseMainWidget m_crrentOperateNum:"<<m_currentOperateNum;
}

void WeeduCourseMainWidget::slot_playPrev()
{
    m_currentOperateNum -= 1;
    if( m_currentOperateNum < 0 )
    {
        emit signal_currentCourseFinish();
    }
    else
    {
        nextOperate( m_currentOperateNum );
    }

    qDebug()<<" WeeduCourseMainWidget m_crrentOperateNum:"<<m_currentOperateNum;
}

void WeeduCourseMainWidget::slot_currentCourseFinish()
{
    m_currentOperateWidget->stopPlayMedia();

    emit signal_currentCourseFinish();
}

void WeeduCourseMainWidget::slot_palyPause()
{
    MediaPlayManager::instance()->mediaPlayOrPause();
}

WeeduCourseMainWidget::~WeeduCourseMainWidget()
{
    delete ui;
}
