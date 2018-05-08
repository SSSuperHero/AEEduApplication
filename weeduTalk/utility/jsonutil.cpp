#include "jsonutil.h"



void fromJson(const QJsonValue& jsonValue, int& ret)
{
    if (jsonValue.isUndefined())
    {
        return;
    }

    if(jsonValue.isString())
        ret = jsonValue.toString().toInt();
    else
        ret = jsonValue.toInt();
}

void fromJson(const QJsonValue& jsonValue, QString& ret)
{
    if (jsonValue.isUndefined())
    {
        return;
    }

    if(jsonValue.isDouble())
        ret = QString::number(jsonValue.toInt());
    else
        ret = jsonValue.toString();
}

void fromJson(const QJsonValue& jsonValue, bool& ret)
{
    if (jsonValue.isUndefined())
    {
        return;
    }

    ret = jsonValue.toBool();
}

void fromJson(const QJsonValue& jsonValue, double& ret)
{
    if (jsonValue.isUndefined())
    {
        return;
    }

    ret = jsonValue.toDouble();
}
