#include "baseentity.h"

BaseEntity::BaseEntity()
{

}

BaseEntity::BaseEntity(int errorCode_, const QString &errorMsg_)
    :errcode(errorCode_)
    ,errdesc(errorMsg_)
{

}

QString BaseEntity::toString() const
{
    return QString("errorCode:%1, errorMsg:%2").arg(errcode).arg(errdesc);
}
