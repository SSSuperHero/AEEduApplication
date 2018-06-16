#ifndef WEEDUPRIMARYSCHOOLUNITITEM_H
#define WEEDUPRIMARYSCHOOLUNITITEM_H

#include <QWidget>
#include "weeduschoolunititembase.h"

namespace Ui {
class WeeduPrimarySchoolUnitItem;
}

class WeeduPrimarySchoolUnitItem : public WeeduSchoolUnitItemBase
{
    Q_OBJECT

public:
    explicit WeeduPrimarySchoolUnitItem(QWidget *parent = 0);

    void bind( const wetalkgetUnitInfo _wetalkgetUnitInfo );

    ~WeeduPrimarySchoolUnitItem();

    void setBackgroundPic(const int _num);

private:
    void showStartsNum(const int _starsNum);

private:
    Ui::WeeduPrimarySchoolUnitItem *ui;

};

#endif // WEEDUPRIMARYSCHOOLUNITITEM_H
