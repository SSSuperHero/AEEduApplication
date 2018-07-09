#ifndef WEEDULESSONGUIDEWIDGET_H
#define WEEDULESSONGUIDEWIDGET_H

#include <QWidget>
#include "weedulessonitembase.h"
#include "mgr/http/echowebhttpapi.h"
#include "utility/jsonutil.h"
#include "utility/widget/clicklabel.h"

struct wetalkselectEventItem
{
    QString     text;
    QString     media_filename;
    QString     media_type;
    QString     timeRange;
};

BEGIN_FROM_JSON(wetalkselectEventItem)
MEMBER_FROM_JSON(text)
MEMBER_FROM_JSON(media_filename)
MEMBER_FROM_JSON(media_type)
MEMBER_FROM_JSON(timeRange)
END_FROM_JSON()

struct wetalkSelectEvents
{
    wetalkselectEventItem Yes;
    wetalkselectEventItem No;
};

BEGIN_FROM_JSON(wetalkSelectEvents)
MEMBER_FROM_JSON(Yes)
MEMBER_FROM_JSON(No)
END_FROM_JSON()

typedef QVector<wetalkSelectEvents> wetalkSelectEvents_t;

//items都可以用这个
struct wetalkDataListItem
{
    bool        isCorrect;
    QString     type;
    QString     text;
    QString     media_filename;
    QString     media_type;
    QString     timeRange;
    QString     item;
};

BEGIN_FROM_JSON(wetalkDataListItem)
MEMBER_FROM_JSON(isCorrect)
MEMBER_FROM_JSON(type)
MEMBER_FROM_JSON(text)
MEMBER_FROM_JSON(media_filename)
MEMBER_FROM_JSON(media_type)
MEMBER_FROM_JSON(timeRange)
MEMBER_FROM_JSON(item)
END_FROM_JSON()

typedef QVector<wetalkDataListItem> wetalkDataListItem_t;

struct wetalkchildEventsItem
{
    QString     score;
    QString     type;
    QString     text;
    QString     media_filename;
    QString     media_type;
    QString     timeRange;
};

BEGIN_FROM_JSON(wetalkchildEventsItem)
MEMBER_FROM_JSON(score)
MEMBER_FROM_JSON(type)
MEMBER_FROM_JSON(text)
MEMBER_FROM_JSON(media_filename)
MEMBER_FROM_JSON(media_type)
MEMBER_FROM_JSON(timeRange)
END_FROM_JSON()

typedef QVector<wetalkchildEventsItem> wetalkchildEventsItem_t;

struct wetalkDataMenu
{
    int         num;
    QString     type;
    QString     text;
    QString     media_filename;
    QString     media_type;
    QString     picture;
};

BEGIN_FROM_JSON(wetalkDataMenu)
MEMBER_FROM_JSON(num)
MEMBER_FROM_JSON(type)
MEMBER_FROM_JSON(text)
MEMBER_FROM_JSON(media_filename)
MEMBER_FROM_JSON(media_type)
MEMBER_FROM_JSON(picture)
END_FROM_JSON()

typedef QVector<wetalkDataMenu> wetalkDataMenu_t;

struct wetalkClickEvents
{
    wetalkchildEventsItem   click_1;
    wetalkchildEventsItem   click_2;
};

BEGIN_FROM_JSON(wetalkClickEvents)
MEMBER_FROM_JSON(click_1)
MEMBER_FROM_JSON(click_2)
END_FROM_JSON()

struct wetalkMultipleChoices
{
    int         num;
    QString     type;
    QString     content_id;
    QString     media_filename;
    QString     media_type;
    QString     timeRange;
    int         scores;
    QString     picture;
    wetalkDataListItem          text;
    wetalkDataListItem_t        items;
    wetalkSelectEvents_t        selectEvents;
};

BEGIN_FROM_JSON(wetalkMultipleChoices)
MEMBER_FROM_JSON(num)
MEMBER_FROM_JSON(type)
MEMBER_FROM_JSON(text)
MEMBER_FROM_JSON(media_filename)
MEMBER_FROM_JSON(media_type)
MEMBER_FROM_JSON(picture)
MEMBER_FROM_JSON(text)
MEMBER_FROM_JSON(items)
MEMBER_FROM_JSON(selectEvents)
END_FROM_JSON()

typedef QVector<wetalkMultipleChoices> wetalkMultipleChoices_t;

struct wetalkDataList
{
    int         num;
    QString     type;
    QString     text;
    QString     timeRange;
    QString     media_filename;
    QString     media_type;
    QString     picture;
    QStringList     pictures;
    wetalkDataListItem_t    items;
//    clickEvents;
};

BEGIN_FROM_JSON(wetalkDataList)
MEMBER_FROM_JSON(num)
MEMBER_FROM_JSON(type)
MEMBER_FROM_JSON(text)
MEMBER_FROM_JSON(media_filename)
MEMBER_FROM_JSON(media_type)
MEMBER_FROM_JSON(picture)
END_FROM_JSON()

typedef QVector<wetalkDataList> wetalkDataList_t;

typedef QVector<QString> QString_t;

struct wetalkevents
{
    int         num;
    QString     type;
    QString     text;
    QString     content;
    QString     timeRange;
    QString     media_filename;
    QString     media_type;
    QString     answer;
    QString     cloze_answer;
    QString     picture;
    QString_t     pictures;
    QString     name;
    QString     avatar;
    QString     role;
    QString     key;
    int     content_id;
    int     scores;
    wetalkDataListItem_t        items;
    wetalkClickEvents           clickEvents;
    wetalkchildEventsItem_t     childEvents;
    wetalkMultipleChoices_t     multipleChoicesList;
    wetalkSelectEvents_t        selectEvents;
};

BEGIN_FROM_JSON(wetalkevents)
MEMBER_FROM_JSON(num)
MEMBER_FROM_JSON(type)
MEMBER_FROM_JSON(text)
MEMBER_FROM_JSON(content)
MEMBER_FROM_JSON(timeRange)
MEMBER_FROM_JSON(media_filename)
MEMBER_FROM_JSON(media_type)
MEMBER_FROM_JSON(answer)
MEMBER_FROM_JSON(cloze_answer)
MEMBER_FROM_JSON(picture)
MEMBER_FROM_JSON(pictures)
MEMBER_FROM_JSON(name)
MEMBER_FROM_JSON(avatar)
MEMBER_FROM_JSON(role)
MEMBER_FROM_JSON(key)
MEMBER_FROM_JSON(content_id)
MEMBER_FROM_JSON(scores)
MEMBER_FROM_JSON(items)
MEMBER_FROM_JSON(clickEvents)
MEMBER_FROM_JSON(childEvents)
MEMBER_FROM_JSON(multipleChoicesList)
MEMBER_FROM_JSON(selectEvents)
END_FROM_JSON()

typedef QVector<wetalkevents> wetalkevents_t;

struct wetalkgetClassInfo
{
    int unit_id;
    int lesson_id;
    int part_id;
    QString media_filename;
    QString sr_category;
    QString media_type;
    int content_totalcount;
    int content_perpage;
    int content_perPageCount;
    QString totalTime;
    QString questions_type;
    QString part_type;
    bool    have_questions;
    wetalkevents_t  keywords;
    wetalkevents_t  dataMenu;
    wetalkevents_t  systems;
    wetalkevents_t  results;
    wetalkevents_t  events;
    wetalkevents_t  dataList;
};

BEGIN_FROM_JSON(wetalkgetClassInfo)
MEMBER_FROM_JSON(unit_id)
MEMBER_FROM_JSON(lesson_id)
MEMBER_FROM_JSON(part_id)
MEMBER_FROM_JSON(media_filename)
MEMBER_FROM_JSON(sr_category)
MEMBER_FROM_JSON(media_type)
MEMBER_FROM_JSON(content_totalcount)
MEMBER_FROM_JSON(content_perpage)
MEMBER_FROM_JSON(content_perPageCount)
MEMBER_FROM_JSON(totalTime)
MEMBER_FROM_JSON(questions_type)
MEMBER_FROM_JSON(part_type)
MEMBER_FROM_JSON(have_questions)
MEMBER_FROM_JSON(keywords)
MEMBER_FROM_JSON(dataMenu)
MEMBER_FROM_JSON(systems)
MEMBER_FROM_JSON(results)
MEMBER_FROM_JSON(events)
END_FROM_JSON()

//一键播放请求
typedef QVector<wetalkgetClassInfo> wetalkgetClassInfo_t;

struct wetalkgetPartInfo
{
    int id;
    QString description;
    QString name;
    QString type;
    int accuracy;
    int completion_rate;
    int scores;
    bool partLock;
    bool testLock;
    QString picture_url;
    QString background_url;
    QString tag_type;
    QString tag_name;
    int event_count;
};

BEGIN_FROM_JSON(wetalkgetPartInfo)
MEMBER_FROM_JSON(id)
MEMBER_FROM_JSON(description)
MEMBER_FROM_JSON(name)
MEMBER_FROM_JSON(type)
MEMBER_FROM_JSON(accuracy)
MEMBER_FROM_JSON(completion_rate)
MEMBER_FROM_JSON(scores)
MEMBER_FROM_JSON(partLock)
MEMBER_FROM_JSON(testLock)
MEMBER_FROM_JSON(picture_url)
MEMBER_FROM_JSON(tag_type)
MEMBER_FROM_JSON(tag_name)
MEMBER_FROM_JSON(event_count)
END_FROM_JSON()

//一键播放请求
typedef QVector<wetalkgetPartInfo> wetalkgetPartInfo_t;

struct wetalkgetPartInfoList
{
    wetalkgetPartInfo_t data;
};

namespace Ui {
class WeEduLessonGuideWidget;
}

class WeEduLessonGuideWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WeEduLessonGuideWidget(QWidget *parent = 0);
    ~WeEduLessonGuideWidget();
    void setLessonInfoAndType (const wetalkgetLessonInfo _lessonInfo, const LESSON_WEEDUSCHOOL_TYPE _lessonType);
    void loadData(const wetalkgetPartInfo_t _partInfoList);

    void setPartFilePath(const QString _filePath);
protected:
    void paintEvent(QPaintEvent *event);
    void analysisPartJson(const int _partId);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_listenButton_clicked();

    void on_readButton_clicked();

    void on_quizButton_clicked();

    void slot_clickPartItem(ClickedLabel *_partItem );

private:
    Ui::WeEduLessonGuideWidget *ui;

    QString                 m_filePath;
};

#endif // WEEDULESSONGUIDEWIDGET_H
