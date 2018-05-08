#include "weeduchooselevelwidget.h"
#include "ui_weeduchooselevelwidget.h"

WeeduChooseLevelWidget::WeeduChooseLevelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeeduChooseLevelWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint );
    setWindowOpacity( 0.6 );
}

WeeduChooseLevelWidget::~WeeduChooseLevelWidget()
{
    delete ui;
}

void WeeduChooseLevelWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit signal_chooseLevelWidgetHide();
}
