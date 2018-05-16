#ifndef WEEDUMAINWIDGET_H
#define WEEDUMAINWIDGET_H

#include <QWidget>
#include "utility/widget/basemainwidget.h"
#include "mgr/http/echowebhttpapi.h"
#include "config/configutil.h"
#include "weeduclassitem.h"
#include "weeduchooselevelwidget.h"
#include "weeduschoolunitwidget.h"

namespace Ui {
class WeeduMainWidget;
}

class WeeduMainWidget : public BaseMainWidget
{
    Q_OBJECT

public:
    explicit WeeduMainWidget(QWidget *parent = 0);

    void init();

    ~WeeduMainWidget();

private:
    void loadWetalkCourseInfoList();
    void loadWetalkgetLevelList(const int _course_id);
    void loadWetalkgetUnitList( const int _course_id,const int _Unit_id );
    UNIT_WEEDUSCHOOL_TYPE getCurrentCourseType( const QString _course_type );

public slots:
    void slot_loginSuccess();

private slots:
    void slot_onGetWetalkgetCourseInfoStart();
    void slot_onGetWetalkgetCourseInfoFinish();
    void slot_onGetWetalkgetCourseInfoSuccess(const QString &response);
    void slot_onGetWetalkgetCourseInfoFailure(const QString &response);

    void slot_onGetWetalkgetLevelListSuccess(const QString &response);
    void slot_onGetWetalkgetLevelListFailure(const QString &response);

    void slot_clickCourse(const int _course_id , const QString _course_type);
    void slot_clickeBack();
    void slot_itemClicked(QListWidgetItem *item);

    void slot_onGetWetalkgetUnitListSuccess(const QString &response);
    void slot_onGetWetalkgetUnitListFailure(const QString &response);
    void on_minButton_clicked();

    void on_maxButton_clicked();

    void on_close_button_clicked();

private:
    Ui::WeeduMainWidget         *ui;

    EntityNetworkReplyHolder    *m_getWetalkgetCourseInfoReply;
    EntityNetworkReplyHolder    *m_getWetalkgetLevelListReply;
    EntityNetworkReplyHolder    *m_getWetalkgetUnitListReply;

    WeeduSchoolUnitWidget       *m_weeduSchoolUnitWidget;

    UNIT_WEEDUSCHOOL_TYPE            m_schoolUnitType;
    int                         m_currentCourseId;

};

#endif // WEEDUMAINWIDGET_H
