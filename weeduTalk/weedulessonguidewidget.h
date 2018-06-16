#ifndef WEEDULESSONGUIDEWIDGET_H
#define WEEDULESSONGUIDEWIDGET_H

#include <QWidget>
#include "weedulessonitembase.h"
#include "mgr/http/echowebhttpapi.h"
#include "utility/jsonutil.h"
#include "utility/widget/clicklabel.h"

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
