#include "weeduchooselevelitem.h"
#include "ui_weeduchooselevelitem.h"
#include <QDebug>

WeeduChooseLevelItem::WeeduChooseLevelItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeeduChooseLevelItem)
{
    ui->setupUi(this);
}



WeeduChooseLevelItem::~WeeduChooseLevelItem()
{
    delete ui;
}

void WeeduChooseLevelItem::setBackgroundPic( const int _num )
{
    QString _styleStr = QString("QWidget#WeeduChooseLevelItemBack \
    { \
    border-image: url(:/images/middle_level%1.png); \
    }").arg(_num+1);

    qDebug()<<"WeeduChooseLevelItem _styleStr:"<<_styleStr;

    ui->WeeduChooseLevelItemBack->setStyleSheet( _styleStr );
}

void WeeduChooseLevelItem::mouseReleaseEvent(QMouseEvent *event)
{
    signal_clickWeeduChooseLevelItem( m_wetalkgetLeveInfo.id );
}

void WeeduChooseLevelItem::bind(const wetalkgetLevelInfo _levelInfo, const int _num)
{
    m_wetalkgetLeveInfo = _levelInfo;

    setBackgroundPic( _num );
}
