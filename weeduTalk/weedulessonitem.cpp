#include "weedulessonitem.h"
#include "ui_weedulessonitem.h"
#include "utility/widget/stylesheetutil.h"
#include "utility/downloadutil.h"

WeeduLessonItem::WeeduLessonItem(QWidget *parent) :
    WeeduLessonItemBase(parent),
    ui(new Ui::WeeduLessonItem)
{
    ui->setupUi(this);
}

void WeeduLessonItem::bind(const wetalkgetLessonInfo _wetalkgetLessonInfo)
{
    DownloadUtil::downloadImage(this, _wetalkgetLessonInfo.picture_url, ui->labelPic,
                                "QLabel#labelPic", false );

    ui->label_name->setText( _wetalkgetLessonInfo.name );
    ui->label_accuracy->setText( QString::number( _wetalkgetLessonInfo.accuracy ) + "%" );
    ui->label_completion->setText( QString::number( _wetalkgetLessonInfo.completion_rate ) + "%" );

    setWeeduSchooLessonlId( _wetalkgetLessonInfo.id );
}

WeeduLessonItem::~WeeduLessonItem()
{
    delete ui;
}
