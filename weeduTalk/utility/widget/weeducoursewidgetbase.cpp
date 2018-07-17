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

void WeeduCourseWidgetBase::stopPlayMedia()
{
    if( m_videoWidget )
        m_videoWidget->setParent(NULL);

    MediaPlayManager::instance()->mediaPause();
}

