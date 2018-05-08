#include "configutil.h"
#include "utility/pathutil.h"

ConfigUtil::ConfigUtil()
{
}

void ConfigUtil::setValue(const QString &key, const QVariant &value)
{
    CREATE_QSETTING();
    setting.setValue(key, value);
    setting.sync();
}

QVariant ConfigUtil::value(const QString &key, const QVariant &defaultValue)
{
    CREATE_QSETTING();
    return setting.value(key, defaultValue);
}

QString ConfigUtil::getSettingApplicationName()
{
    return PathUtil::getApplicationDirPath() + SETTING_APPLICATION_NAME;
}
