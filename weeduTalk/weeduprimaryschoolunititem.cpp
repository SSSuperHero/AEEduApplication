#include "weeduprimaryschoolunititem.h"
#include "ui_weeduprimaryschoolunititem.h"

WeeduPrimarySchoolUnitItem::WeeduPrimarySchoolUnitItem(QWidget *parent) :
    WeeduSchoolUnitItemBase(parent),
    ui(new Ui::WeeduPrimarySchoolUnitItem)
{
    ui->setupUi(this);
}

void WeeduPrimarySchoolUnitItem::showStartsNum( const int _starsNum )
{
    ui->labelStar1->setStyleSheet("border-image: url(:/images/primary_starOff.png);");
    ui->labelStar2->setStyleSheet("border-image: url(:/images/primary_starOff.png);");
    ui->labelStar3->setStyleSheet("border-image: url(:/images/primary_starOff.png);");

    switch (_starsNum)
    {
    case 1:
        ui->labelStar1->setStyleSheet("border-image: url(:/images/primary_StarOn.png);");
        break;

    case 2:
        ui->labelStar1->setStyleSheet("border-image: url(:/images/primary_StarOn.png);");
        ui->labelStar2->setStyleSheet("border-image: url(:/images/primary_StarOn.png);");
        break;

    case 3:
        ui->labelStar1->setStyleSheet("border-image: url(:/images/primary_StarOn.png);");
        ui->labelStar2->setStyleSheet("border-image: url(:/images/primary_StarOn.png);");
        ui->labelStar3->setStyleSheet("border-image: url(:/images/primary_StarOn.png);");
        break;

    default:
        break;
    }
}

void WeeduPrimarySchoolUnitItem::bind(const wetalkgetUnitInfo _wetalkgetUnitInfo)
{
    setWeeduSchoolId( _wetalkgetUnitInfo.id );

    showStartsNum( _wetalkgetUnitInfo.stars );
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
