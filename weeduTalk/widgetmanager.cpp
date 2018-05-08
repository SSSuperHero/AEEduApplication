#include "widgetmanager.h"

WidgetManager::WidgetManager(QObject *parent) :
    QObject(parent),
    m_loginWidget( NULL ),
    m_weeduMainWidget( NULL )
{

    init();

}

void WidgetManager::init()
{
    m_loginWidget = new WeeduLoginWidget();
    connect( m_loginWidget, &WeeduLoginWidget::signal_loginSuccess, this, &WidgetManager::slot_loginSuccess );
    m_loginWidget->show();

    m_weeduMainWidget = new WeeduMainWidget();
    connect( m_loginWidget, &WeeduLoginWidget::signal_loginSuccess, m_weeduMainWidget, &WeeduMainWidget::slot_loginSuccess );
    m_weeduMainWidget->hide();
}

void WidgetManager::slot_loginSuccess()
{
    m_loginWidget->hide();
    m_weeduMainWidget->show();
}
