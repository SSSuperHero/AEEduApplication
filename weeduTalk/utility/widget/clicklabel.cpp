#include "clicklabel.h"
#include <QDebug>
#include <QPainter>

ClickedLabel::ClickedLabel(QString str,QWidget *parent):
    QLabel(parent),
    m_infoId(0)
{
    setText(str);
}

ClickedLabel::ClickedLabel(QWidget *parent):
    QLabel(parent)
{

}

void ClickedLabel::paintEvent(QPaintEvent *e)
{
    if( NULL != pixmap() )
    {
       QPainter painter(this);
       painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
       QPainterPath path;
       int round = qMin(width(), height());
       path.addEllipse(0, 0, round, round);
       painter.setClipPath(path);
       painter.drawPixmap(-1, -1, width()+2, height()+2, *pixmap());
//       if(m_bTransLayer)
//       {
//            //鼠标在label上，加载透明图片
//            QPixmap pixMap(":/user_change.png");
//            painter.drawPixmap(-1, -1, width()+2, height()+2, pixMap);
//       }
    }
    else
    {
       QLabel::paintEvent(e);
    }
}

void ClickedLabel::mouseReleaseEvent(QMouseEvent *e)
{
    emit Clicked( this );

    QWidget::mouseReleaseEvent(e);
}

void ClickedLabel::setDataInfo( const int _infoId, const int _totleIndex, const int _curIndex )
{
    m_infoId = _infoId;
    m_totleIndex = _totleIndex;
    m_curIndex = _curIndex;
}

int ClickedLabel::getInfoId()
{
    return m_infoId;
}

int ClickedLabel::getTotleIndex()
{
    return m_totleIndex;
}

int ClickedLabel::getCurrentIndex()
{
    return m_curIndex;
}

