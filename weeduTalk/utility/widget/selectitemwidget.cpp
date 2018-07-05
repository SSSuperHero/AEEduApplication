#include "selectitemwidget.h"
#include "ui_selectitemwidget.h"

SelectItemWidget::SelectItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectItemWidget)
{
    ui->setupUi(this);
}

SelectItemWidget::~SelectItemWidget()
{
    delete ui;
}
