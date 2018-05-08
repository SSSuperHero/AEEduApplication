#ifndef ECHOHTTPINFOENTITY_H
#define ECHOHTTPINFOENTITY_H

#include "utility/jsonutil.h"

struct echoBellEditInfo
{
    int         id;
    int         sound_id;
    int         times;
    QString     start_time;
    QString     end_time;
    QString     sound_source;
    QString     name;
    int         bell_id;
};
BEGIN_FROM_JSON(echoBellEditInfo)
MEMBER_FROM_JSON(id)
MEMBER_FROM_JSON(sound_id)
MEMBER_FROM_JSON(times)
MEMBER_FROM_JSON(start_time)
MEMBER_FROM_JSON(end_time)
MEMBER_FROM_JSON(sound_source)
MEMBER_FROM_JSON(name)
MEMBER_FROM_JSON(bell_id)
END_FROM_JSON()

struct echoBellInfo
{
    QString coins;
    int is_buy;
    QString coins_vip;
};
BEGIN_FROM_JSON(echoBellInfo)
MEMBER_FROM_JSON(coins)
MEMBER_FROM_JSON(is_buy)
MEMBER_FROM_JSON(coins_vip)
END_FROM_JSON()

#endif // ECHOHTTPINFOENTITY_H
