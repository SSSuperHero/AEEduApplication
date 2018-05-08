#ifndef ECHOWEBWIDGET_H
#define ECHOWEBWIDGET_H
#include <QWebEngineView>
#include "webView/myqwebengineurlrequestinterceptor.h"
#include <QWebEngineHistory>
#include "config/define.h"

class EchoWebWidget : public QWebEngineView
{
    Q_OBJECT

public:
    EchoWebWidget(QWidget *parent = 0);

    void load_url(const QString _url, bool _reLoadFlag = false );

    void loadMvInfoPage(const QString &_mvId);
    void loadeSearchPage(const QString &_searchStr);
    void updateWebPage(const WEB_PAGE_TYPE &_webPage, bool _flag = false );
    void loadSoundInfoPage(const QString &_soundId);

    void testUrl(const QString _url);
    void setCurrentZoomFactor(double _zoomFactorNum);
signals:
    void signal_loadFinish(bool);

private:
    QString getBaseUrl(const QString &_url);

public slots:
    void gotoBack();
    void gotoForward();

    void slot_clearCefCookie();
private:
    QString                     m_url;
    bool                        m_reloadFlag;

    MyQWebEngineUrlRequestInterceptor *m_webInterceptor;
    QWebEngineHistory                 *m_webEngineHistory;
};

#endif // ECHOWEBWIDGET_H
