#include "weedumiddleschoolunititem.h"
#include "ui_weedumiddleschoolunititem.h"
#include "utility/widget/stylesheetutil.h"
#include "utility/downloadutil.h"

WeeduMiddleSchoolUnitItem::WeeduMiddleSchoolUnitItem(QWidget *parent) :
    WeeduSchoolUnitItemBase(parent),
    ui(new Ui::WeeduMiddleSchoolUnitItem)
{
    ui->setupUi(this);
}

void WeeduMiddleSchoolUnitItem::showStartsNum( const int _starsNum )
{
    ui->labelStar1->setStyleSheet("border-image: url(:/images/middle_StarOff.png);");
    ui->labelStar2->setStyleSheet("border-image: url(:/images/middle_StarOff.png);");
    ui->labelStar3->setStyleSheet("border-image: url(:/images/middle_StarOff.png);");

    switch (_starsNum)
    {
    case 1:
        ui->labelStar1->setStyleSheet("border-image: url(:/images/middle_StarOn.png);");
        break;

    case 2:
        ui->labelStar1->setStyleSheet("border-image: url(:/images/middle_StarOn.png);");
        ui->labelStar2->setStyleSheet("border-image: url(:/images/middle_StarOn.png);");
        break;

    case 3:
        ui->labelStar1->setStyleSheet("border-image: url(:/images/middle_StarOn.png);");
        ui->labelStar2->setStyleSheet("border-image: url(:/images/middle_StarOn.png);");
        ui->labelStar3->setStyleSheet("border-image: url(:/images/middle_StarOn.png);");
        break;

    default:
        break;
    }
}

void WeeduMiddleSchoolUnitItem::bind(const wetalkgetUnitInfo _wetalkgetUnitInfo)
{
    DownloadUtil::downloadImage(this, _wetalkgetUnitInfo.picture_url, ui->labelPic,
                                "QLabel#labelPic", false );

    ui->labelName->setText( _wetalkgetUnitInfo.name );

    setWeeduSchoolId( _wetalkgetUnitInfo.id );

    showStartsNum( _wetalkgetUnitInfo.stars );

}

WeeduMiddleSchoolUnitItem::~WeeduMiddleSchoolUnitItem()
{
    delete ui;
}
