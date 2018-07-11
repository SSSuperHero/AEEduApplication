#include "bottomcontrolwidget.h"
#include "ui_bottomcontrolwidget.h"

BottomControlWidget::BottomControlWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::BottomControlWidget)
{
    ui->setupUi(this);

    reSetSize( ui->pushButtonSpeak );
    reSetSize( ui->pushButtonAgain );
    reSetSize( ui->pushButtonListen );
    reSetSize( ui->pushButtonNext );
    reSetSize( ui->pushButtonPause );
    reSetSize( ui->pushButtonPrev );
    reSetSize( ui->pushButtonSpeak );
}

BottomControlWidget::~BottomControlWidget()
{
    delete ui;
}

void BottomControlWidget::on_pushButtonPause_clicked()
{
    emit signal_palyPause();
}

void BottomControlWidget::on_pushButtonPrev_clicked()
{
    emit signal_playPrev();
}

void BottomControlWidget::on_pushButtonNext_clicked()
{
    emit signal_playNext();
}

void BottomControlWidget::on_pushButtonAgain_clicked()
{
    emit signal_playRepeat();
}

void BottomControlWidget::on_pushButtonSpeak_clicked()
{
    emit signal_sr();
}

void BottomControlWidget::on_pushButtonListen_clicked()
{
    emit signal_listen();
}
