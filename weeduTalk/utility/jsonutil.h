#ifndef JSONUTIL_H
#define JSONUTIL_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

/*
 *
BEGIN_TO_JSON(Person)
MEMBER_TO_JSON(name)
MEMBER_TO_JSON(sex)
MEMBER_TO_JSON(age)
MEMBER_TO_JSON(children)
END_TO_JSON()
 *
 */

template<typename T>
QJsonValue toJsonValue(const T& t)
{
    return QJsonValue(t);
}

template<typename T>
QJsonValue toJsonValue(const QVector<T>& vecItems)
{
    QJsonArray jsonArray;
    foreach (const T& item, vecItems)
    {
        jsonArray.append(toJsonValue(item));
    }

    return jsonArray;
}


template<typename Entity>
QString toJson(const Entity& entity)
{
    QJsonValue jsonValue = toJsonValue(entity);
    QJsonDocument jsonDoc(jsonValue.toObject());
    return jsonDoc.toJson(QJsonDocument::Compact);
}

template<typename T>
QString toJson(const QVector<T>& entity)
{
    QJsonValue jsonValue = toJsonValue(entity);
    QJsonDocument jsonDoc(jsonValue.toArray());
    return jsonDoc.toJson(QJsonDocument::Compact);
}


#define BEGIN_TO_JSON(Person) \
    inline QJsonValue toJsonValue(const Person& person) \
    { \
        QJsonObject jsonObject;

#define MEMBER_TO_JSON(member) \
    jsonObject[#member] = toJsonValue(person.member);

#define END_TO_JSON() \
    return jsonObject; \
    }

//----------------------------------------------------------------------------------------

/*
 *
BEGIN_FROM_JSON(Person)
MEMBER_FROM_JSON(name)
MEMBER_FROM_JSON(sex)
MEMBER_FROM_JSON(age)
MEMBER_FROM_JSON(children)
END_FROM_JSON()
 *
 */

void fromJson(const QJsonValue& jsonValue, int& ret);

void fromJson(const QJsonValue& jsonValue, QString& ret);

void fromJson(const QJsonValue& jsonValue, bool& ret);

void fromJson(const QJsonValue& jsonValue, double& ret);



template<typename T>
void fromJson(const QJsonValue& jsonValue, QVector<T>& vecItems)
{
    if (jsonValue.isUndefined())
    {
        return;
    }

    vecItems.clear();

    QJsonArray jsonArray = jsonValue.toArray();
    for (int i = 0; i < jsonArray.size(); ++i)
    {
        T child;
        fromJson(jsonArray.at(i), child);
        vecItems.append(child);
    }
}

template<typename T>
bool fromJson(const QString& json, T& t)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8(), &parseError);
    if (parseError.error != QJsonParseError::NoError)
    {
        qCritical("parse json error:%d, json:%s", parseError.error, qUtf8Printable(json));
        return false;
    }

    QJsonObject root = doc.object();
    fromJson(root, t);

    return true;
}

#define BEGIN_FROM_JSON(Person) \
    inline void fromJson(const QJsonValue& jsonValue, Person& person) \
    {\
        QJsonObject jsonObj = jsonValue.toObject();

#define MEMBER_FROM_JSON(member) \
    fromJson(jsonObj.take(#member), person.member);

#define END_FROM_JSON() \
    }







#endif // JSONUTIL_H
