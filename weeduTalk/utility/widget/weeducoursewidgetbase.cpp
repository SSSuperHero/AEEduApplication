#include "weeducoursewidgetbase.h"
#include "mgr/media/mediaplaymanager.h"

WeeduCourseWidgetBase::WeeduCourseWidgetBase(QWidget *parent) :
    BaseMainWidget(parent),
    m_currentOperateNum(0),
    m_videoWidget(NULL)
{

}

void WeeduCourseWidgetBase::loadData(const wetalkevents _dataInfo, const int _currentOperateNum)
{

}

void WeeduCourseWidgetBase::slot_playNext()
{
    stopPlayMedia();

    m_currentOperateNum += 1;
    emit signal_currentOperateFinish( m_currentOperateNum );

    qDebug()<<" WeeduCourseWidgetBase m_crrentOperateNum:"<<m_currentOperateNum;
}

void WeeduCourseWidgetBase::stopPlayMedia()
{
    if( m_videoWidget )
        m_videoWidget->setParent(NULL);

    MediaPlayManager::instance()->mediaPause();
}

void WeeduCourseWidgetBase::slot_playPrev()
{
    stopPlayMedia();

    m_currentOperateNum -= 1;

    if( m_currentOperateNum < 0 )
    {
        emit signal_currentCourseFinish();
    }
    else
    {
        emit signal_currentOperateFinish( m_currentOperateNum - 1 );
    }

    qDebug()<<"WeeduCourseWidgetBase m_crrentOperateNum:"<<m_currentOperateNum;
}

void WeeduCourseWidgetBase::slot_palyPause()
{

}

