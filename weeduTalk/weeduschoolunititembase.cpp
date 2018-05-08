#include "weeduschoolunititembase.h"
#include "weedumiddleschoolunititem.h"
#include "weeduhighschoolunititem.h"
#include "weeduprimaryschoolunititem.h"
#include "weeduhighschoollesson.h"
#include "weedulessonitem.h"

UNIT_WEEDUSCHOOL_TYPE WeeduSchoolUnitItemBase::m_weeduSchoolType = HIGHSCHOOL_UNIT_ITEM;
WeeduSchoolUnitItemBase::WeeduSchoolUnitItemBase(QWidget *parent) :
    QWidget(parent),
    m_weeduSchoolId( 0 )
{

}

void WeeduSchoolUnitItemBase::bind(const wetalkgetUnitInfo _wetalkgetUnitInfo)
{

}

void WeeduSchoolUnitItemBase::setWeeduSchoolId( const int _id )
{
    m_weeduSchoolId = _id;
}

WeeduSchoolUnitItemBase *WeeduSchoolUnitItemBase::newSchoolUnitItem(QWidget *owner , const UNIT_WEEDUSCHOOL_TYPE _unitType)
{
    WeeduSchoolUnitItemBase * _weeduSchoolUnitItem = NULL;
    m_weeduSchoolType = _unitType;

    switch ( _unitType )
    {
    case HIGHSCHOOL_UNIT_ITEM:
        _weeduSchoolUnitItem = new WeeduHighSchoolUnitItem( owner );
        break;

    case MIDDLESCHOOL_UNIT_ITEM:
        _weeduSchoolUnitItem = new WeeduMiddleSchoolUnitItem( owner );
        break;

    case PRIMARYSCHOOL_UNIT_ITEM:
        _weeduSchoolUnitItem = new WeeduPrimarySchoolUnitItem( owner );
        break;

    default:
        break;
    }

    return _weeduSchoolUnitItem;
}

void WeeduSchoolUnitItemBase::mouseReleaseEvent(QMouseEvent *event)
{
    emit signal_clickSchoolUnitItem( m_weeduSchoolId, m_weeduSchoolType );

    QWidget::mouseReleaseEvent( event );
}
