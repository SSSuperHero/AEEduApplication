#include "weedumainwidget.h"
#include "ui_weedumainwidget.h"
#include <QDebug>
#include "utility/userinfo.h"

WeeduMainWidget::WeeduMainWidget(QWidget *parent) :
    BaseMainWidget(parent),
    ui(new Ui::WeeduMainWidget),
    m_currentCourseId( 0 )
{
    ui->setupUi(this);

    init();
}

void WeeduMainWidget::init()
{
    setResizeEnabled( true );

    m_weeduSchoolUnitWidget = new WeeduSchoolUnitWidget();
    connect( m_weeduSchoolUnitWidget, &WeeduSchoolUnitWidget::signal_clickeBack,
             this, &WeeduMainWidget::slot_clickeBack );
    connect( m_weeduSchoolUnitWidget, &WeeduSchoolUnitWidget::signal_clickWeeduChooseLevelItem,
             this, &WeeduMainWidget::slot_clickWeeduChooseLevelItem );

    m_weeduSchoolUnitWidget->hide();

    connect( ui->listWidget, &QListWidget::itemClicked, this, &WeeduMainWidget::slot_itemClicked );
}

void WeeduMainWidget::slot_loginSuccess()
{
    loadWetalkCourseInfoList();

    ui->label_head->setPixmap( QPixmap(userInfoMgr::instance()->getUserInfo().avatar_url) );
}

void WeeduMainWidget::slot_clickWeeduChooseLevelItem(const int _leaveId)
{
    loadWetalkgetUnitList( m_currentCourseId, _leaveId );
}

void WeeduMainWidget::loadWetalkCourseInfoList()
{

    m_getWetalkgetCourseInfoReply = EchoWebHttpApi::instance()->getWetalkCourseInfoList( this );

    connect(m_getWetalkgetCourseInfoReply, &EntityNetworkReplyHolder::signal_onStart,
            this, &WeeduMainWidget::slot_onGetWetalkgetCourseInfoStart);
    connect(m_getWetalkgetCourseInfoReply, &EntityNetworkReplyHolder::signal_onFinish,
            this, &WeeduMainWidget::slot_onGetWetalkgetCourseInfoFinish);
    connect(m_getWetalkgetCourseInfoReply, &EntityNetworkReplyHolder::signal_onSuccess,
            this, &WeeduMainWidget::slot_onGetWetalkgetCourseInfoSuccess);
    connect(m_getWetalkgetCourseInfoReply, &EntityNetworkReplyHolder::signal_onError,
            this, &WeeduMainWidget::slot_onGetWetalkgetCourseInfoFailure);
}

void WeeduMainWidget::slot_onGetWetalkgetCourseInfoStart()
{


}

void WeeduMainWidget::slot_onGetWetalkgetCourseInfoFinish()
{

}

void WeeduMainWidget::slot_onGetWetalkgetCourseInfoSuccess(const QString &response)
{
    qInfo()<<"slot_onGetWetalkgetCourseInfoSuccess response:"<<response;

    HttpEntity<wetalkgetCourseInfo_t> _wetalkgetCourseInfo;
    fromJson( response, _wetalkgetCourseInfo );

    ui->listWidget->clear();

    foreach ( const wetalkgetCourseInfo &_wetalkgetCourseInfoItem, _wetalkgetCourseInfo.data )
    {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        WeeduClassItem *timetableItem = new WeeduClassItem(ui->listWidget);
        timetableItem->bindData( _wetalkgetCourseInfoItem );

        ui->listWidget->setItemWidget(item,timetableItem);

        connect( timetableItem, &WeeduClassItem::signal_clickCourse, this, &WeeduMainWidget::slot_clickCourse );
    }

}

void WeeduMainWidget::slot_onGetWetalkgetCourseInfoFailure(const QString& response)
{
    qInfo()<<"slot_onWebLoginFailure response:"<<response;

//    HttpEntity<loginDetailsInfoEntity> loginDetailsInfo;
//    fromJson( response, loginDetailsInfo );

//    loginFinish( loginDetailsInfo.message );

}

void WeeduMainWidget::slot_onGetWetalkgetLevelListSuccess(const QString &response)
{
    qInfo()<<"slot_onGetWetalkgetCourseInfoSuccess response:"<<response;

    HttpEntity<wetalkgetLevelInfo_t> _wetalkgetLevelInfo;
    fromJson( response, _wetalkgetLevelInfo );

    if( _wetalkgetLevelInfo.data.size() < 1 )
        return;

    m_weeduSchoolUnitWidget->upWeeduChooseLevelInfoList( _wetalkgetLevelInfo.data );
    loadWetalkgetUnitList( m_currentCourseId, _wetalkgetLevelInfo.data.at(0).id );
}

void WeeduMainWidget::slot_onGetWetalkgetLevelListFailure(const QString &response)
{

}

UNIT_WEEDUSCHOOL_TYPE WeeduMainWidget::getCurrentCourseType( const QString _course_type )
{
    UNIT_WEEDUSCHOOL_TYPE _type;

    if( _course_type.compare("high_school") == 0 )
        _type = HIGHSCHOOL_UNIT_ITEM;
    else if( _course_type.compare("middle_school") == 0 )
        _type = MIDDLESCHOOL_UNIT_ITEM;
    else
        _type = PRIMARYSCHOOL_UNIT_ITEM;

    return _type;
}

void WeeduMainWidget::slot_clickCourse( const int _course_id, const QString _course_type  )
{
    qDebug()<<"slot_clickCourse _course_id:"<<_course_id;
    m_currentCourseId = _course_id;

    m_schoolUnitType = getCurrentCourseType( _course_type );
    loadWetalkgetLevelList( m_currentCourseId );
}

void WeeduMainWidget::slot_clickeBack()
{
    m_weeduSchoolUnitWidget->hide();
    this->show();
}

void WeeduMainWidget::slot_itemClicked( QListWidgetItem *item )
{
//    loadWetalkgetLevelList( 2 );
}

void WeeduMainWidget::loadWetalkgetLevelList( const int _course_id )
{
    m_getWetalkgetLevelListReply = EchoWebHttpApi::instance()->getWetalkgetLevelList( this, _course_id );

    connect(m_getWetalkgetLevelListReply, &EntityNetworkReplyHolder::signal_onSuccess,
            this, &WeeduMainWidget::slot_onGetWetalkgetLevelListSuccess);
    connect(m_getWetalkgetLevelListReply, &EntityNetworkReplyHolder::signal_onError,
            this, &WeeduMainWidget::slot_onGetWetalkgetLevelListFailure);
}

void WeeduMainWidget::loadWetalkgetUnitList( const int _course_id,const int _Unit_id )
{
    m_getWetalkgetUnitListReply = EchoWebHttpApi::instance()->getWetalkUnitList( this, _course_id, _Unit_id  );

    connect(m_getWetalkgetUnitListReply, &EntityNetworkReplyHolder::signal_onSuccess,
            this, &WeeduMainWidget::slot_onGetWetalkgetUnitListSuccess);
    connect(m_getWetalkgetUnitListReply, &EntityNetworkReplyHolder::signal_onError,
            this, &WeeduMainWidget::slot_onGetWetalkgetUnitListFailure);
}

void WeeduMainWidget::slot_onGetWetalkgetUnitListSuccess(const QString &response)
{
    qInfo()<<"slot_onGetWetalkgetCourseInfoSuccess response:"<<response;

    HttpEntity<wetalkgetUnitInfo_t> _wetalkgetUnitInfo;
    fromJson( response, _wetalkgetUnitInfo );

    qDebug()<<"slot_onGetWetalkgetUnitListSuccess size:"<<_wetalkgetUnitInfo.data.size();
    if( _wetalkgetUnitInfo.data.size() < 1 )
        return;

    m_weeduSchoolUnitWidget->upSchoolUnitWidget( _wetalkgetUnitInfo.data, m_schoolUnitType );
    m_weeduSchoolUnitWidget->show();
    this->hide();
}

void WeeduMainWidget::slot_onGetWetalkgetUnitListFailure(const QString &response)
{

}

WeeduMainWidget::~WeeduMainWidget()
{
    if( m_weeduSchoolUnitWidget )
    {
        delete m_weeduSchoolUnitWidget;
        m_weeduSchoolUnitWidget = NULL;
    }

    delete ui;
}
