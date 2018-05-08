#include "weeduhighschoolunititem.h"
#include "ui_weeduhighschoolunititem.h"

WeeduHighSchoolUnitItem::WeeduHighSchoolUnitItem(QWidget *parent) :
    WeeduSchoolUnitItemBase(parent),
    ui(new Ui::WeeduHighSchoolUnitItem)
{
    ui->setupUi(this);
}

void WeeduHighSchoolUnitItem::bind(const wetalkgetUnitInfo _wetalkgetUnitInfo)
{
    setWeeduSchoolId( _wetalkgetUnitInfo.id );

    ui->label_name->setText( _wetalkgetUnitInfo.name );
    ui->label_text->setText( _wetalkgetUnitInfo.description );
    ui->label_accuracy->setText( QString::number(_wetalkgetUnitInfo.accuracy) );
    ui->label_completion->setText( QString::number(_wetalkgetUnitInfo.completion_rate) );
    ui->label_MT->setText( QString::number(_wetalkgetUnitInfo.scores) );
}

WeeduHighSchoolUnitItem::~WeeduHighSchoolUnitItem()
{
    delete ui;
}
