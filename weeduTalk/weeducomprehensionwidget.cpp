#include "weeducomprehensionwidget.h"
#include "ui_weeducomprehensionwidget.h"
#include "utility/widget/selectitemwidget.h"
#include "mgr/media/mediaplaymanager.h"
#include "lessonRouter/weedulessonrouter.h"
#include <QDebug>

WeeduComprehensionWidget::WeeduComprehensionWidget(QWidget *parent) :
    WeeduCourseWidgetBase(parent),
    ui(new Ui::WeeduComprehensionWidget),
    m_crrentOperateNum(0),
    m_itemNum(0),
    m_multipleChoicesNum(0)
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
    connect( m_bottomControlWidget, &BottomControlWidget::signal_playPrev,
             this, &WeeduComprehensionWidget::slot_playPrev );
//    connect( m_bottomControlWidget, &BottomControlWidget::signal_palyPause,
//             this, &WeeduComprehensionWidget::slot_palyPause );

    m_headControlWidget = new HeadControlWidget( this );
    ui->verticalLayout_head->addWidget( m_headControlWidget );

    m_topControlWidget = new TopControlWidget( this );
    ui->verticalLayout_head->addWidget( m_topControlWidget );
    connect( m_topControlWidget, &TopControlWidget::signal_back,
             this, &WeeduComprehensionWidget::signal_currentCourseFinish );

}

void WeeduComprehensionWidget::operaterMedia( const QString _mediaType, const QString _mediaFile )
{
    QString _videoFile = WeeduLessonRouter::instance()->getCourseResourceFilePath() + "/" + _mediaFile;

    if (_mediaType == "audio")
    {
        MediaPlayManager::instance()->startPlayVideo( _videoFile );
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

    operaterMedia( m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).media_type,
                   m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).media_filename);

    clearLayout( ui->verticalLayout );
    foreach (wetalkDataListItem _itemData, m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).items)
    {
        SelectItemWidget *_selectItem = new SelectItemWidget(this);
        _selectItem->bindData( "", _itemData );
        ui->verticalLayout->addWidget( _selectItem );
    }
}

void WeeduComprehensionWidget::showSelect()
{
    m_dataItemType = DATA_SELECT;
    wetalkSelectEvents _itemData = m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).selectEvents.at(0);

    clearLayout( ui->verticalLayout );
    operaterMedia( _itemData.Yes.media_type,
                   _itemData.Yes.media_filename);

    SelectItemWidget *_selectItem = new SelectItemWidget(this);
    _selectItem->bindData( "", _itemData.Yes );
    ui->verticalLayout->addWidget( _selectItem );

    SelectItemWidget *_selectItem1 = new SelectItemWidget(this);
    _selectItem1->bindData( "", _itemData.No );
    ui->verticalLayout->addWidget( _selectItem1 );
}

void WeeduComprehensionWidget::loadData( const wetalkevents _dataInfo, const int _currentOperateNum )
{
    m_operateDataInfo = _dataInfo;
    m_crrentOperateNum = _currentOperateNum;

    if( m_operateDataInfo.multipleChoicesList.size() < 1 )
        return;

    m_multipleChoicesNum = 0;

    m_topControlWidget->setShowText( m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).text.text );

//    qDebug()<<"WeeduComprehensionWidget initDataInfo size:"<< m_operateDataInfo.multipleChoicesList.at(0).items.size()<<m_operateDataInfo.num;
    if( m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).items.size() > 0 )
    {
        showItems();
    }
    else if( m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).selectEvents.size() > 0 )
    {
        showSelect();
    }
}

void WeeduComprehensionWidget::slot_playNext()
{
    if( m_dataItemType == DATA_SELECT || ( m_dataItemType == DATA_ITEM &&
                                          m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).selectEvents.size() < 1 ) )
    {
        m_multipleChoicesNum += 1;

        if( m_operateDataInfo.multipleChoicesList.size() <= m_multipleChoicesNum )
        {
            emit signal_currentOperateFinish( m_crrentOperateNum + 1 );
            MediaPlayManager::instance()->mediaPlayStop();
        }
        else
        {
            if( m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).items.size() > 0 )
            {
               showItems();
            }
            else if( m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).selectEvents.size() > 0 )
            {
                showSelect();
            }
        }

    }
    else
    {
        showSelect();
    }

    qDebug()<<"m_multipleChoicesNum:"<<m_multipleChoicesNum;
    qDebug()<<" WeeduComprehensionWidget size:"<<m_operateDataInfo.multipleChoicesList.size();
}

void WeeduComprehensionWidget::slot_playPrev()
{
    if( m_dataItemType == DATA_ITEM || ( m_dataItemType == DATA_SELECT &&
                                          m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).items.size() < 1 ) )
    {
        m_multipleChoicesNum -= 1;
        if( m_multipleChoicesNum < 0 )
        {
            m_crrentOperateNum -= 1;
            if( m_crrentOperateNum < 0 )
            {
                emit signal_currentCourseFinish();
            }
            else
            {
                emit signal_currentOperateFinish( m_crrentOperateNum - 1 );
                MediaPlayManager::instance()->mediaPlayStop();
            }
            return;
        }

        if( m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).items.size() > 0 )
        {
            showItems();
        }
        else if( m_operateDataInfo.multipleChoicesList.at(m_multipleChoicesNum).selectEvents.size() > 0 )
        {
            showSelect();
        }
    }
    else
    {
        showItems();
    }

    qDebug()<<"m_multipleChoicesNum:"<<m_multipleChoicesNum;
    qDebug()<<" WeeduComprehensionWidget size:"<<m_operateDataInfo.multipleChoicesList.size();
}

void WeeduComprehensionWidget::slot_palyPause()
{

}

WeeduComprehensionWidget::~WeeduComprehensionWidget()
{
    delete ui;
}
