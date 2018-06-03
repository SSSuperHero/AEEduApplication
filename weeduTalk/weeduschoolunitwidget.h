#ifndef WEEDUSCHOOLUNITWIDGET_H
#define WEEDUSCHOOLUNITWIDGET_H

#include <QWidget>
#include "weeduschoolunititembase.h"
#include "utility/widget/basemainwidget.h"
#include "weeduchooselevelwidget.h"
#include "mgr/http/echowebhttpapi.h"
#include "weedulessonitembase.h"
#include "weedulessonguidewidget.h"

namespace Ui {
class WeeduSchoolUnitWidget;
}

enum WEEDUSCHOOL_ITEM_TYPE
{
    WEEDUSCHOOL_ITEM_UNIT,
    WEEDUSCHOOL_ITEM_LESSON
};

class WeeduSchoolUnitWidget : public BaseMainWidget
{
    Q_OBJECT

public:
    explicit WeeduSchoolUnitWidget(QWidget *parent = 0);
    ~WeeduSchoolUnitWidget();

    void upSchoolUnitWidget(const wetalkgetUnitInfo_t &_wetalkgetUnitInfoList, const UNIT_WEEDUSCHOOL_TYPE _unitType);
    void upSchoolLessonWidget(const wetalkgetLessonInfo_t &_wetalkgetLessonInfoList, const LESSON_WEEDUSCHOOL_TYPE _lessonType);
    void upWeeduChooseLevelInfoList(const wetalkgetLevelInfo_t _levelInfoList);
private:
    void updateBackgroundPic(const UNIT_WEEDUSCHOOL_TYPE _unitType);
    int getCurrentRowNum(const int _unitType);
    void loadWetalkgetLessonList(const int _unit_id);
    void upLoadWetalkPart(const int _Part_id);

signals:
    void signal_clickeBack();
    void signal_clickWeeduChooseLevelItem( const int _leaveId );

private slots:
    void on_pushButton_clicked();
    void slot_showChooseLevelItemWidget();
    void slot_hideChooseLevelItemWidget();

    void slot_onGetWetalkgetLessonListSuccess(const QString &response);
    void slot_onGetWetalkgetLessonListFailure(const QString &response);

    void slot_onGetWetalkgetPartListSuccess(const QString &response);
    void slot_onGetWetalkgetPartListFailure(const QString &response);

    void slot_clickSchoolUnitItem( const int _id, const UNIT_WEEDUSCHOOL_TYPE _type );
    void slot_clickSchoolLessonItem(const wetalkgetLessonInfo _lessonInfo, const LESSON_WEEDUSCHOOL_TYPE _type );

private:
    Ui::WeeduSchoolUnitWidget *ui;

    QWidget                     *m_layoutWidgetbase;
    WeeduChooseLevelWidget      *m_chooseLevelItemWidget;
    WeEduLessonGuideWidget      *m_lessonGuideWidget;
    EntityNetworkReplyHolder    *m_getWetalkgetLessonListReply;
    EntityNetworkReplyHolder    *m_getWetalkgetPartListReply;

    UNIT_WEEDUSCHOOL_TYPE       m_weeduSchoolUnitType;
    LESSON_WEEDUSCHOOL_TYPE     m_weeduSchoolLessonType;
    WEEDUSCHOOL_ITEM_TYPE       m_weeduSchoolItemType;

    wetalkgetUnitInfo_t         m_weeduChooseUnitInfoList;
    wetalkgetLessonInfo_t       m_weeduChooseLessonInfoList;

};

#endif // WEEDUSCHOOLUNITWIDGET_H
