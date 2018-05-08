#include "userinfo.h"
#include <QDebug>

void userInfoMgr::init()
{

}

void userInfoMgr::setToken(const QString &_token)
{
    m_token = _token;
    qInfo()<<"setToken m_token:"<<m_token;
}

void userInfoMgr::setUserInfo(const loginDetailsInfoEntity &_info)
{
    m_userInfo = _info;
}

loginDetailsInfoEntity userInfoMgr::getUserInfo()
{
    return m_userInfo;
}

QString userInfoMgr::getToken()
{
    qInfo()<<"getToken m_token:"<<m_token;
    return m_token;
}
