#ifndef STRINGUTILITY_H
#define STRINGUTILITY_H

#include <QString>
#include <QFont>

class StringUtility
{
public:
    StringUtility();

public:
    static bool splitPair(const QString& pair, const QString& seperator, QString& first, QString& second);
    // 返回字符串容器中，字符宽度最大的索引， maxWide：最长字符串宽度(像素), 用户白板文本输入
    static bool getLongestLine(const QFont &font, const QStringList& lines, int& maxWide, int& maxIndex);
    static QString timeTostring(const int &_second);

    static bool hasNewVersion(const QString &latestVersion);
    static QString getHostIpAddress();
    static QString getHostMacAddress();
    static QString geteElidedText(QFont font, QString str, int MaxWidth);
};

#endif // STRINGUTILITY_H
