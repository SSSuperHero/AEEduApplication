#include "weeduhighschoollesson.h"
#include "ui_weeduhighschoollesson.h"
#include "utility/widget/stylesheetutil.h"
#include "utility/downloadutil.h"

WeeduHighSchoolLesson::WeeduHighSchoolLesson(QWidget *parent) :
    WeeduLessonItemBase(parent),
    ui(new Ui::WeeduHighSchoolLesson)
{
    ui->setupUi(this);
}

WeeduHighSchoolLesson::~WeeduHighSchoolLesson()
{
    delete ui;
}

void WeeduHighSchoolLesson::bind(const wetalkgetLessonInfo _wetalkgetLessonInfo)
{
    DownloadUtil::downloadImage(this, _wetalkgetLessonInfo.picture_url, ui->labelPic,
                                "QLabel#labelPic", false );

    ui->label_name->setText( _wetalkgetLessonInfo.name );
    ui->label_text->setText( _wetalkgetLessonInfo.description );
    ui->label_Num->setText( QString::number( _wetalkgetLessonInfo.accuracy ) + "%" );
//    ui->label_type->setText( _wetalkgetLessonInfo.description );

    setWeeduSchooLessonlId( _wetalkgetLessonInfo );
}

