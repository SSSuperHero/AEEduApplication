#include "weeduschoolunitwidget.h"
#include "ui_weeduschoolunitwidget.h"
#include <QDebug>
#include "utility/userinfo.h"
#include "weeduprimaryschoolunititem.h"

WeeduSchoolUnitWidget::WeeduSchoolUnitWidget(QWidget *parent) :
    BaseMainWidget(parent),
    ui(new Ui::WeeduSchoolUnitWidget),
    m_layoutWidgetbase ( NULL ),
    m_weeduSchoolItemType( WEEDUSCHOOL_ITEM_UNIT )
{
    ui->setupUi(this);

    setResizeEnabled( true );
    ui->labelHighSchool->hide();

    m_chooseLevelItemWidget = new WeeduChooseLevelWidget();
    m_chooseLevelItemWidget->hide();
    connect( m_chooseLevelItemWidget, &WeeduChooseLevelWidget::signal_chooseLevelWidgetHide,
             this, &WeeduSchoolUnitWidget::slot_hideChooseLevelItemWidget );
    connect( ui->widgetChoose, &windgetLabel::signal_clickWidgetItem,
             this, &WeeduSchoolUnitWidget::slot_showChooseLevelItemWidget );
    m_lessonGuideWidget = new WeEduLessonGuideWidget();
    m_lessonGuideWidget->hide();

    ui->label_head->setPixmap( QPixmap( userInfoMgr::instance()->getUserInfo().avatar_url ) );
}

void WeeduSchoolUnitWidget::clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0)) != 0)
    {
        //删除widget
        if(item->widget())
        {
            delete item->widget();
            //item->widget()->deleteLater();
        }
        //删除子布局
        QLayout *childLayout = item->layout();
        if(childLayout)
        {
            clearLayout(childLayout);
        }
        delete item;
    }
}

void WeeduSchoolUnitWidget::updateBackgroundPic( const UNIT_WEEDUSCHOOL_TYPE _unitType )
{
    QString _style;

    if( _unitType == HIGHSCHOOL_UNIT_ITEM )
    {
        ui->widgetChoose->hide();
        ui->labelHighSchool->show();
    }
    else
    {
        ui->widgetChoose->show();
        ui->labelHighSchool->hide();
    }

    m_weeduSchoolUnitType = _unitType;

    switch ( _unitType )
    {
    case HIGHSCHOOL_UNIT_ITEM:
//    case HIGHSCHOOL_LESSON_ITEM:
        _style = "/images/high_bg.png";
        break;

    case MIDDLESCHOOL_UNIT_ITEM:
//    case MIDDLESCHOOL_LESSON_ITEM:
        _style = "/images/middle_bg.png";
        break;

    case PRIMARYSCHOOL_UNIT_ITEM:
//    case PRIMARYSCHOOL_LESSON_ITEM:
        _style = "/images/primary_bg.png";
        break;
    default:
        break;
    }

    ui->widgetBack->setStyleSheet(QString("QWidget#widgetBack \
    {\
    border-image: url(:%1);\
    }").arg(_style) );

}

int WeeduSchoolUnitWidget::getCurrentRowNum( const int _unitType )
{
    int _rowNum = 0;
    switch ( _unitType )
    {
    case 0:
        _rowNum = 3;
        break;

    case 1:
    case 2:
        _rowNum = 4;
        break;

    case 3:
        _rowNum = 2;
        break;

    case 4:
    case 5:
        _rowNum = 3;
        break;
    default:
        break;
    }

    return _rowNum;

}

void WeeduSchoolUnitWidget::upSchoolUnitWidget( const wetalkgetUnitInfo_t &_wetalkgetUnitInfoList, const UNIT_WEEDUSCHOOL_TYPE _unitType )
{

    qDebug()<<"upSchoolUnitWidget size:"<<_wetalkgetUnitInfoList.size();
    qDebug()<<"upSchoolUnitWidget countNum:"<<ui->unitItemLayout->count();

    m_weeduSchoolItemType = WEEDUSCHOOL_ITEM_UNIT;
    m_weeduChooseUnitInfoList = _wetalkgetUnitInfoList;

    ui->label_name->setText( _wetalkgetUnitInfoList.at(0).name );

    int _rowNum = getCurrentRowNum( _unitType );
    updateBackgroundPic( _unitType );

    clearLayout( ui->unitItemLayout );

    if( m_layoutWidgetbase )
    {
        delete m_layoutWidgetbase;
        m_layoutWidgetbase = NULL;
    }
    m_layoutWidgetbase = new QWidget( this );

    for( int i = 0; i < _wetalkgetUnitInfoList.size(); i++ )
    {
        WeeduSchoolUnitItemBase *infoItem = WeeduSchoolUnitItemBase::newSchoolUnitItem( m_layoutWidgetbase, _unitType );
        infoItem->bind( _wetalkgetUnitInfoList.at(i) );

        if( _unitType == PRIMARYSCHOOL_UNIT_ITEM )
        {
            ((WeeduPrimarySchoolUnitItem *)infoItem)->setBackgroundPic( i );
        }

        connect( infoItem, &WeeduSchoolUnitItemBase::signal_clickSchoolUnitItem,
                 this, &WeeduSchoolUnitWidget::slot_clickSchoolUnitItem );

        ui->unitItemLayout->addWidget( infoItem, i/_rowNum, i%_rowNum );
    }
}

void WeeduSchoolUnitWidget::upSchoolLessonWidget(const wetalkgetLessonInfo_t &_wetalkgetLessonInfoList,
                                                 const LESSON_WEEDUSCHOOL_TYPE _lessonType )
{

    qDebug()<<"upSchoolLessonWidget size:"<<_wetalkgetLessonInfoList.size();
    qDebug()<<"upSchoolLessonWidget countNum:"<<ui->unitItemLayout->count();

    m_weeduSchoolItemType = WEEDUSCHOOL_ITEM_LESSON;
    m_weeduChooseLessonInfoList = _wetalkgetLessonInfoList;

    int _rowNum = getCurrentRowNum( _lessonType + 3 );
    updateBackgroundPic( m_weeduSchoolUnitType );

    clearLayout( ui->unitItemLayout );

    if( m_layoutWidgetbase )
    {
        delete m_layoutWidgetbase;
        m_layoutWidgetbase = NULL;
    }
    m_layoutWidgetbase = new QWidget( this );

    for( int i = 0; i < _wetalkgetLessonInfoList.size(); i++ )
    {
        WeeduLessonItemBase *infoItem = WeeduLessonItemBase::newSchoolLessonItem( m_layoutWidgetbase, _lessonType );
        infoItem->bind( _wetalkgetLessonInfoList.at(i) );

        connect( infoItem, &WeeduLessonItemBase::signal_clickSchoolLessonItem,
                 this, &WeeduSchoolUnitWidget::slot_clickSchoolLessonItem );

        ui->unitItemLayout->addWidget( infoItem, i/_rowNum, i%_rowNum );
    }
}

WeeduSchoolUnitWidget::~WeeduSchoolUnitWidget()
{
    if( m_chooseLevelItemWidget )
    {
        delete m_chooseLevelItemWidget;
        m_chooseLevelItemWidget = NULL;
    }

    delete ui;
}

void WeeduSchoolUnitWidget::on_pushButton_clicked()
{
    if( m_weeduSchoolItemType == WEEDUSCHOOL_ITEM_UNIT )
        emit signal_clickeBack();
    else
        upSchoolUnitWidget( m_weeduChooseUnitInfoList, m_weeduSchoolUnitType );
}

void WeeduSchoolUnitWidget::slot_showChooseLevelItemWidget()
{
    ui->widgetChoose->hide();
    m_chooseLevelItemWidget->setGeometry( this->geometry() );
    m_chooseLevelItemWidget->show();
}

void WeeduSchoolUnitWidget::slot_hideChooseLevelItemWidget()
{
    ui->widgetChoose->show();
    m_chooseLevelItemWidget->hide();
}

void WeeduSchoolUnitWidget::loadWetalkgetLessonList( const int _unit_id )
{
    m_getWetalkgetLessonListReply = EchoWebHttpApi::instance()->getWetalkUnitItem( this,  _unit_id  );

    connect(m_getWetalkgetLessonListReply, &EntityNetworkReplyHolder::signal_onSuccess,
            this, &WeeduSchoolUnitWidget::slot_onGetWetalkgetLessonListSuccess);
    connect(m_getWetalkgetLessonListReply, &EntityNetworkReplyHolder::signal_onError,
            this, &WeeduSchoolUnitWidget::slot_onGetWetalkgetLessonListFailure);
}

void WeeduSchoolUnitWidget::slot_onGetWetalkgetLessonListSuccess(const QString &response)
{
    qInfo()<<"slot_onGetWetalkgetLessonListSuccess response:"<<response;

    HttpEntity<wetalkgetLessonInfo_t> _wetalkgetLessonInfo;
    fromJson( response, _wetalkgetLessonInfo );

    upSchoolLessonWidget( _wetalkgetLessonInfo.data, m_weeduSchoolLessonType );
}

void WeeduSchoolUnitWidget::slot_onGetWetalkgetLessonListFailure(const QString &response)
{

}

void WeeduSchoolUnitWidget::slot_clickSchoolUnitItem(const int _id, const UNIT_WEEDUSCHOOL_TYPE _type)
{
    loadWetalkgetLessonList( _id );

    switch (_type)
    {
    case HIGHSCHOOL_UNIT_ITEM:
        m_weeduSchoolLessonType = HIGHSCHOOL_LESSON_ITEM;
        break;

    case MIDDLESCHOOL_UNIT_ITEM:
        m_weeduSchoolLessonType = MIDDLESCHOOL_LESSON_ITEM;
        break;

    case PRIMARYSCHOOL_UNIT_ITEM:
        m_weeduSchoolLessonType = PRIMARYSCHOOL_LESSON_ITEM;
        break;

    default:
        break;
    }
}

void WeeduSchoolUnitWidget::slot_clickSchoolLessonItem( const wetalkgetLessonInfo _lessonInfo, const LESSON_WEEDUSCHOOL_TYPE _type )
{
    m_lessonGuideWidget->setGeometry(this->geometry());
    m_lessonGuideWidget->show();
    m_lessonGuideWidget->setLessonInfoAndType(_lessonInfo,_type);
}
