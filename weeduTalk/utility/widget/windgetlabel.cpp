#include "windgetlabel.h"
#include "utility/stringutility.h"
#include <QDebug>


windgetLabel::windgetLabel(QWidget *parent) :
    BaseWidget(parent)
{
    initUI();
}
windgetLabel::~windgetLabel()
{
    delete m_label;
}

void windgetLabel::setBindData( const QString &str, const QVariant& var, const SEARCH_MUSIC_TYPE &_searchType )
{
    m_var = var;
//    m_label->setStyleSheet(QString("margin-left: %1px;").arg(20));
    set_label_str( str );
    m_searchType = _searchType;
}

void windgetLabel::set_label_str( const QString &str )
{
    m_str = str;
    m_label->setText( str );
}
void windgetLabel::initUI()
{
    m_label = new QLabel(this);

//    m_label->setFont(QFont("微软雅黑",8,false));
    reSetFont( QFont("微软雅黑",8,false), m_label );
}
void windgetLabel::mousePressEvent(QMouseEvent *e)
{
    emit signal_searchItem( m_var, m_searchType );

    QWidget::mousePressEvent(e);
}

void windgetLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit signal_doubleClickItem();

    QWidget::mouseDoubleClickEvent(event);
}

void windgetLabel::mouseReleaseEvent(QMouseEvent *event)
{
    emit signal_clickWidgetItem();
}
void windgetLabel::resizeEvent(QResizeEvent *)
{
    m_label->setGeometry(0,0,width(),height());
    QFont font( m_label->font() );
    QFontMetrics fm(font);
    m_label->setText( fm.elidedText(m_str, Qt::ElideRight, m_label->width()) );
}
