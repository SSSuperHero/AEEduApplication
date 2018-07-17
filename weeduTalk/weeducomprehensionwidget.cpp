#include "weeducomprehensionwidget.h"
#include "ui_weeducomprehensionwidget.h"
#include "utility/widget/selectitemwidget.h"
#include "mgr/media/mediaplaymanager.h"
#include "lessonRouter/weedulessonrouter.h"
#include "utility/stringutility.h"
#include <QTimer>
#include <QDebug>

WeeduComprehensionWidget::WeeduComprehensionWidget(QWidget *parent) :
    WeeduCourseWidgetBase(parent),
    ui(new Ui::WeeduComprehensionWidget),
    m_itemNum(0),
    m_multipleChoicesNum(0)
{
    ui->setupUi(this);

    init();
}

void WeeduComprehensionWidget::init()
{

}

void WeeduComprehensionWidget::operaterMedia( wetalkMultipleChoices _multipleChoicesData )
{
    QString _mediaType = _multipleChoicesData.media_type;
    QString _mediaFile = _multipleChoicesData.media_filename;
    QString _timeRange = _multipleChoicesData.timeRange;

    QString _videoFile = WeeduLessonRouter::instance()->getCourseResourceFilePath() + "/" + _mediaFile;

    if (_mediaType == "audio")
    {
        int _startTime = 0;
        int _endTime = 0;
        StringUtility::stringToTime( _timeRange, _startTime, _endTime );
        MediaPlayManager::instance()->startPlayMidea( _videoFile, _startTime, _endTime );
    }
    else if (_mediaType == "video")
    {
//        QString _videoFile = WeeduLessonRouter::instance()->getCourseResourceFilePath() + "/" + _mediaFile;

//        m_videoWidget =  MediaPlayManager::instance()->startPlayVideo( _videoFile, 3000, 9000 );

//        ui->labelPic->hide();
//        ui->widgetChooseItem->hide();
//        ui->horizontalLayout->addWidget( m_videoWidget );
    }
    else if (_mediaType == "image")
    {
        ui->labelPic->setStyleSheet(QString("border-image: url(%1);").arg(_videoFile));
    }

}

void WeeduComprehensionWidget::showItems()
{
    m_dataItemType = DATA_ITEM;

    operaterMedia( m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum) );

    clearLayout( ui->verticalLayout );
    foreach (wetalkDataListItem _itemData, m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).items)
    {
        SelectItemWidget *_selectItem = new SelectItemWidget(this);
        _selectItem->bindData( "", _itemData );
        ui->verticalLayout->addWidget( _selectItem );

        connect( _selectItem, &SelectItemWidget::signal_selectFinish,
                 this, &WeeduComprehensionWidget::slot_chooseFinish);
    }
}

void WeeduComprehensionWidget::showSelect()
{
    m_dataItemType = DATA_SELECT;
    wetalkSelectEvents _itemData = m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).selectEvents.at(0);

    clearLayout( ui->verticalLayout );
    operaterMedia( m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum) );

    SelectItemWidget *_selectItem = new SelectItemWidget(this);
    _selectItem->bindData( "", _itemData.Yes );
    ui->verticalLayout->addWidget( _selectItem );
    connect( _selectItem, &SelectItemWidget::signal_selectFinish,
             this, &WeeduComprehensionWidget::slot_chooseFinish);

    SelectItemWidget *_selectItem1 = new SelectItemWidget(this);
    _selectItem1->bindData( "", _itemData.No );
    ui->verticalLayout->addWidget( _selectItem1 );
    connect( _selectItem1, &SelectItemWidget::signal_selectFinish,
             this, &WeeduComprehensionWidget::slot_chooseFinish);
}

void WeeduComprehensionWidget::loadData( const wetalkevents _dataInfo, const int _currentOperateNum )
{
    m_operateDataInfo = _dataInfo;
    m_currentOperateNum = _currentOperateNum;

    if( m_operateDataInfo.multipleChoicesList.size() < 1 )
        return;

    m_multipleChoicesNum = 0;

//    m_topControlWidget->setShowText( m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).text.text );

    qDebug()<<"WeeduComprehensionWidget initDataInfo size:"<< m_operateDataInfo.multipleChoicesList.at(0).items.size()<<m_operateDataInfo.num;
    if( m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).items.size() > 0 )
    {
        showItems();
    }
    else if( m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).selectEvents.size() > 0 )
    {
        showSelect();
    }

    qDebug()<<"WeeduComprehensionWidget initDataInfo size:"<< m_operateDataInfo.multipleChoicesList.at(0).items.size()<<m_operateDataInfo.num;
}

void WeeduComprehensionWidget::slot_chooseFinish()
{
//    QTimer::singleShot( 2*1000, this, &WeeduComprehensionWidget::slot_playNext );
}

WeeduComprehensionWidget::~WeeduComprehensionWidget()
{
    delete ui;
}
