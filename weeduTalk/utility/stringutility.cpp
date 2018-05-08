#include "stringutility.h"
#include <QFontMetrics>
#include "config/echoconfig.h"
#include <QNetworkInterface>
#include <QList>
#include <QDebug>

StringUtility::StringUtility()
{

}

QString StringUtility::geteElidedText(QFont font, QString str, int MaxWidth)
{
    QFontMetrics fontWidth(font);
    int width = fontWidth.width(str);  //计算字符串宽度
    qDebug()<<"width of abcdefg"<<fontWidth.width("abcdefg...");  //qDebug获取"abcdefg..." 为60
    if(width>=MaxWidth)  //当字符串宽度大于最大宽度时进行转换
    {
        str = fontWidth.elidedText(str,Qt::ElideRight,MaxWidth);  //右部显示省略号
    }
    return str;   //返回处理后的字符串
}

QString StringUtility::timeTostring( const int &_second )
{
    QString timeStr("");
    int tns, thh, tmm, tss;

    if( _second > -1 )
    {
        tns = _second;
        thh  = tns / 3600;
        tmm  = (tns % 3600) / 60;
        tss  = (tns % 60);
        timeStr.sprintf("%02d:%02d",tmm,tss);
    }

    return timeStr;
}

bool StringUtility::hasNewVersion(const QString &latestVersion)
{
    qInfo("hasNewVersion:%s", qUtf8Printable(latestVersion));
    QStringList partsCurrent = QString(ECHO_APP_VERSION).split(".");
    QStringList partsLatest = latestVersion.split(".");

    if (partsCurrent.size() != 3 || partsLatest.size() != 3)
    {
        qCritical("version parts size incorrect");
        return false;
    }

    if (partsLatest[0].toInt() != partsCurrent[0].toInt())
    {
        return partsLatest[0].toInt() > partsCurrent[0].toInt();
    }

    if (partsLatest[1].toInt() != partsCurrent[1].toInt())
    {
        return partsLatest[1].toInt() > partsCurrent[1].toInt();
    }

    if (partsLatest[2].toInt() != partsCurrent[2].toInt())
    {
        return partsLatest[2].toInt() > partsCurrent[2].toInt();
    }

    return false;
}

bool StringUtility::splitPair(const QString& pair, const QString& seperator, QString& first, QString& second)
{
    int p = pair.indexOf(seperator);
    if (p == -1)
    {
        qCritical("style:%s doesn't contain : sign", qUtf8Printable(pair));
        return false;
    }

    first = pair.left(p).trimmed();
    second = pair.mid(p + 1).trimmed();

    return true;
}

bool StringUtility::getLongestLine(const QFont &font, const QStringList &lines, int& _maxWide, int& _maxIndex)
{
    if(lines.isEmpty())
    {
        qWarning() << "lines is empty.";
        return false;
    }
    int maxWide = 0;
    int maxIndex = 0;
    QFontMetrics metric(font);
    for(int i = 0; i < lines.size(); i ++)
    {
        const QString& line = lines.at(i);
        int wide = metric.width(line);
        if(wide > maxWide)
        {
            maxWide = wide;
            maxIndex = i;
        }
//        qDebug() << QString("[%1] line:%2 wide:%3").arg(i).arg(line).arg(wide);
    }
    _maxWide = maxWide;
    _maxIndex = maxIndex;
    qInfo() << QString("maxWide:%1 maxIndex:%2 LongestText:%3").arg(maxWide).arg(maxIndex).arg(lines.at(maxIndex));
    return true;
}

QString StringUtility::getHostIpAddress()
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
           if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
               ipAddressesList.at(i).toIPv4Address()) {
               strIpAddress = ipAddressesList.at(i).toString();
               break;
           }
     }
     // 如果没有找到，则以本地IP地址为IP
     if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();

     qDebug()<<"getHostIpAddress strIpAddress:"<<strIpAddress;
     return strIpAddress;
}

QString StringUtility::getHostMacAddress()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表
    int nCnt = nets.count();
    QString strMacAddr = "";
    for(int i = 0; i < nCnt; i ++)
    {
        // 如果此网络接口被激活并且正在运行并且不是回环地址，则就是我们需要找的Mac地址
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning) && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            strMacAddr = nets[i].hardwareAddress();
            break;
        }
    }

    qDebug()<<"getHostMacAddress strMacAddr:"<<strMacAddr;
    return strMacAddr;
}
