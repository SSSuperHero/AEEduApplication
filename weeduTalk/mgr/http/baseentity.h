#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <QString>
#include "utility/jsonutil.h"

class BaseEntity
{
public:
    BaseEntity();
    BaseEntity(int errorCode_, const QString& errorMsg_);
    QString toString() const;
    int         errcode;
    QString     errdesc;

};

BEGIN_FROM_JSON(BaseEntity)
MEMBER_FROM_JSON(errcode)
MEMBER_FROM_JSON(errdesc)
END_FROM_JSON()


template<typename DataType>
class HttpEntity: public BaseEntity
{
public:
    DataType        data;
};

template<typename DataType>
BEGIN_FROM_JSON(HttpEntity<DataType>)
MEMBER_FROM_JSON(errcode)
MEMBER_FROM_JSON(errdesc)
MEMBER_FROM_JSON(data)
END_FROM_JSON()


#endif // BASEENTITY_H
