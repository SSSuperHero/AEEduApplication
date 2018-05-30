#include "weeduchooselevelwidget.h"
#include "ui_weeduchooselevelwidget.h"
#include <QPainter>
#include <QDebug>

WeeduChooseLevelWidget::WeeduChooseLevelWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::WeeduChooseLevelWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint );
    setAttribute(Qt::WA_TranslucentBackground, true);
}

WeeduChooseLevelWidget::~WeeduChooseLevelWidget()
{
    delete ui;
}

void WeeduChooseLevelWidget::bindWeeduChooseLevelInfoList(const wetalkgetLevelInfo_t _levelInfoList)
{
    m_WeeduChooseLevelInfoList = _levelInfoList;

    qDebug()<<"WeeduChooseLevelWidget size:"<<_levelInfoList.size();
    qDebug()<<"WeeduChooseLevelWidget countNum:"<<ui->widgetLevelLayout->count();

    ui->label_name->setText( _levelInfoList.at(0).name );

    int _rowNum = 4;

    clearLayout( ui->widgetLevelLayout );

    if( m_layoutWidgetbase )
    {
        delete m_layoutWidgetbase;
        m_layoutWidgetbase = NULL;
    }
    m_layoutWidgetbase = new QWidget( this );

    for( int i = 0; i < _levelInfoList.size(); i++ )
    {
        WeeduChooseLevelItem *infoItem = new WeeduChooseLevelItem( m_layoutWidgetbase );
        infoItem->bind( _levelInfoList.at(i), i );

        connect( infoItem, &WeeduChooseLevelItem::signal_clickWeeduChooseLevelItem,
                 this, &WeeduChooseLevelWidget::signal_clickWeeduChooseLevelItem );
        connect( infoItem, &WeeduChooseLevelItem::signal_clickWeeduChooseLevelItem,
                 this, &WeeduChooseLevelWidget::signal_chooseLevelWidgetHide );

        ui->widgetLevelLayout->addWidget( infoItem, i/_rowNum, i%_rowNum );
    }
}

void WeeduChooseLevelWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(100, 100, 100, 100));
}

void WeeduChooseLevelWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit signal_chooseLevelWidgetHide();
}
