#ifndef WEEDUHIGHSCHOOLUNITITEM_H
#define WEEDUHIGHSCHOOLUNITITEM_H

#include <QWidget>
#include "weeduschoolunititembase.h"

namespace Ui {
class WeeduHighSchoolUnitItem;
}

class WeeduHighSchoolUnitItem : public WeeduSchoolUnitItemBase
{
    Q_OBJECT

public:
    explicit WeeduHighSchoolUnitItem(QWidget *parent = 0);

    void bind( const wetalkgetUnitInfo _wetalkgetUnitInfo );

    ~WeeduHighSchoolUnitItem();

private:
    Ui::WeeduHighSchoolUnitItem *ui;
};

#endif // WEEDUHIGHSCHOOLUNITITEM_H
