#ifndef WEEDUMIDDLESCHOOLUNITITEM_H
#define WEEDUMIDDLESCHOOLUNITITEM_H

#include <QWidget>
#include "weeduschoolunititembase.h"

namespace Ui {
class WeeduMiddleSchoolUnitItem;
}

class WeeduMiddleSchoolUnitItem : public WeeduSchoolUnitItemBase
{
    Q_OBJECT

public:
    explicit WeeduMiddleSchoolUnitItem(QWidget *parent = 0);

    void bind( const wetalkgetUnitInfo _wetalkgetUnitInfo );

    ~WeeduMiddleSchoolUnitItem();

private:
    void showStartsNum(const int _starsNum);

private:
    Ui::WeeduMiddleSchoolUnitItem *ui;
};

#endif // WEEDUMIDDLESCHOOLUNITITEM_H
