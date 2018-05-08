#include "weeduprimaryschoolunititem.h"
#include "ui_weeduprimaryschoolunititem.h"

WeeduPrimarySchoolUnitItem::WeeduPrimarySchoolUnitItem(QWidget *parent) :
    WeeduSchoolUnitItemBase(parent),
    ui(new Ui::WeeduPrimarySchoolUnitItem)
{
    ui->setupUi(this);
}

void WeeduPrimarySchoolUnitItem::bind(const wetalkgetUnitInfo _wetalkgetUnitInfo)
{
    setWeeduSchoolId( _wetalkgetUnitInfo.id );
}

void WeeduPrimarySchoolUnitItem::setBackgroundPic( const int _num )
{
    QString _styleStr = QString("QWidget#widgetPrimarySchoolUnitItem \
    { \
    border-image: url(:/images/primary_unit%1.png); \
    }").arg(_num+1);

    ui->widgetPrimarySchoolUnitItem->setStyleSheet( _styleStr );
}

WeeduPrimarySchoolUnitItem::~WeeduPrimarySchoolUnitItem()
{
    delete ui;
}
