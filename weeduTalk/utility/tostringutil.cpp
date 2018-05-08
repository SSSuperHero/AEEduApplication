#include "tostringutil.h"


QString ToStringUtil::mapToString(const QMap<QString, QString> &stringMap)
{
    QString ret;
    QMap<QString, QString>::const_iterator b = stringMap.begin();
    QMap<QString, QString>::const_iterator e = stringMap.end();
    for (; b != e; ++b)
    {
        ret += QString("key:%1, value:%2").arg(b.key()).arg(b.value());
    }

    return ret;
}

QString ToStringUtil::toString(const QRect &rect)
{
    return QString("left:%1, top:%2, width:%3, height:%4").arg(rect.left()).arg(rect.top()).arg(rect.width()).arg(rect.height());
}
