#include "weeduclassitem.h"
#include "ui_weeduclassitem.h"
#include "utility/widget/stylesheetutil.h"
#include "utility/downloadutil.h"

#pragma execution_character_set("utf-8")

WeeduClassItem::WeeduClassItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeeduClassItem)
{
    ui->setupUi(this);
}

void WeeduClassItem::bindData( const wetalkgetCourseInfo _courseInfo )
{
    m_courseInfo = _courseInfo;

    DownloadUtil::downloadImage(this, _courseInfo.picture_url, ui->labelPic,
                                "QLabel#labelPic", false );

    ui->labelClassType->setText( _courseInfo.name );
    ui->labelObject->setText( _courseInfo.suitable_object );
    ui->labelObjectives->setText( _courseInfo.learning_goals );
    ui->labelClassProperty->setText( _courseInfo.nature_course );

}

void WeeduClassItem::mouseReleaseEvent(QMouseEvent *event)
{
    emit signal_clickCourse( m_courseInfo.id, m_courseInfo.type );

    QWidget::mouseReleaseEvent(event);
}

WeeduClassItem::~WeeduClassItem()
{
    delete ui;
}
