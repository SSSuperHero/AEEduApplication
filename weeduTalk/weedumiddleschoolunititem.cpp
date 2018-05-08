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

void WeeduMiddleSchoolUnitItem::bind(const wetalkgetUnitInfo _wetalkgetUnitInfo)
{
    DownloadUtil::downloadImage(this, _wetalkgetUnitInfo.picture_url, ui->labelPic,
                                "QLabel#labelPic", false );

    ui->labelName->setText( _wetalkgetUnitInfo.name );

    setWeeduSchoolId( _wetalkgetUnitInfo.id );

}

WeeduMiddleSchoolUnitItem::~WeeduMiddleSchoolUnitItem()
{
    delete ui;
}
