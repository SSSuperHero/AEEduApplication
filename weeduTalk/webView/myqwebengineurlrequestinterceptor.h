#ifndef MYQWEBENGINEURLREQUESTINTERCEPTOR_H
#define MYQWEBENGINEURLREQUESTINTERCEPTOR_H
#include <QWebEngineUrlRequestInterceptor>

class MyQWebEngineUrlRequestInterceptor : public QWebEngineUrlRequestInterceptor
{
public:
    MyQWebEngineUrlRequestInterceptor();

    void interceptRequest(QWebEngineUrlRequestInfo &info);

    void setReloadFlag( const bool _flag );

    bool get_header(QWebEngineUrlRequestInfo &info);
private:
    bool            m_reloadFlag;
};

#endif // MYQWEBENGINEURLREQUESTINTERCEPTOR_H
