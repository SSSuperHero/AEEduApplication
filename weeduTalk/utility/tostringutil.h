#ifndef TOSTRINGUTIL_H
#define TOSTRINGUTIL_H

#include <QMap>
#include <QVector>
#include <QPair>
#include <QRect>

class ToStringUtil
{
public:
    static QString mapToString(const QMap<QString, QString>& stringMap);

    template<typename First, typename Second>
    static QString mapToString(const QMap<First, Second>& itemMap)
    {
        QString ret;
#ifndef Q_OS_MAC
        QMap<First, Second>::const_iterator b = itemMap.begin();
        QMap<First, Second>::const_iterator e = itemMap.end();
        for (; b != e; ++b)
        {
            ret += QString("key:%1, value:%2").arg(b.key()).arg(b.value().toString());
        }
#endif
        return ret;
    }

    template<typename T>
    static QString vectorToString(const QVector<T>& items)
    {
        QString ret;
#ifndef Q_OS_MAC
        QVector<T>::const_iterator b = items.begin();
        QVector<T>::const_iterator e = items.end();
        for (; b != e ;++b)
        {
            ret += toString(*b);
        }
#endif
        return ret;
    }

    template<typename T>
    static QString toString(const T& t)
    {
        return t.toString();
    }

    template<typename First, typename Second>
    static QString toString(const QPair<First, Second>& pair)
    {
        return QString("pair(%1,%2)").arg(pair.first).arg(pair.second);
    }

    static QString toString(const QRect& rect);
};

#endif // TOSTRINGUTIL_H
