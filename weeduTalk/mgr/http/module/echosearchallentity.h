#ifndef ECHOSEARCHALLENTITY_H
#define ECHOSEARCHALLENTITY_H

#include "utility/jsonutil.h"

struct echoSearchInfo
{
    int id;
    int sound_id;
    QString name;
    QString info;
};
BEGIN_FROM_JSON(echoSearchInfo)
MEMBER_FROM_JSON(id)
MEMBER_FROM_JSON(sound_id)
MEMBER_FROM_JSON(name)
MEMBER_FROM_JSON(info)
END_FROM_JSON()

typedef QVector<echoSearchInfo> echoSearchInfos_t;

struct EchoSearchAllInfos
{
    echoSearchInfos_t sound;
    echoSearchInfos_t channel;
    echoSearchInfos_t tv;
    echoSearchInfos_t bell;
};

BEGIN_FROM_JSON(EchoSearchAllInfos)
MEMBER_FROM_JSON(sound)
MEMBER_FROM_JSON(channel)
MEMBER_FROM_JSON(tv)
MEMBER_FROM_JSON(bell)
END_FROM_JSON()

#endif // ECHOSEARCHALLENTITY_H
