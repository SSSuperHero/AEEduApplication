#ifndef CONFIGUTIL_H
#define CONFIGUTIL_H

#include <QString>
#include <QSettings>

#define SETTING_OGNIZATION_NAME "echoApplication"
#define SETTING_APPLICATION_NAME "echoRemember"

#define CREATE_QSETTING() QSettings setting(SETTING_OGNIZATION_NAME, ConfigUtil::getSettingApplicationName())

class ConfigUtil
{
public:
    ConfigUtil();

    static void setValue(const QString &key, const QVariant &value);
    static QVariant value(const QString &key, const QVariant &defaultValue = QVariant());
    static QString getSettingApplicationName();

};

#endif // CONFIGUTIL_H
