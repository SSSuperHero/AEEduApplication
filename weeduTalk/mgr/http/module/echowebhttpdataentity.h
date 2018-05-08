#ifndef ECHOWEBHTTPDATAENTITY_H
#define ECHOWEBHTTPDATAENTITY_H

#include "utility/jsonutil.h"

struct loginDetailsInfoEntity
{
    int id;
    QString phone;
    QString email;
    QString name;
    QString access_token;
    int shareout_times;
    QString language;
    QString url;
    QString link;
    QString photo;
    QString avatar_url;
    QString signature;
    QString followed_count;
    QString last_login_ip;
    QString last_login_time;
    int create_time;
    QString create_ip;
    QString email_key;
    int email_key_time;
    int status;
    QString background;
    QString theme;
    QString homepage;
    int auto_tag;
    int activity_privacy;
    int activity_amount;
    QString intro;
    int channel;
    QString redirect;
    int source;
    int echo_webtag;
    int famous_status;
    QString pay_expiry;
    QString last_pay_time;
    int pay_status;
    QString total_pay;
    int pay_class;
    QString cash;
    int coins;
    QString total_income;
    QString total_withdrawal;
    QString city;
    int constellation;
    QString birthday;
    int last_pay_product;
    int can_send_feed;
    int can_down_img;
    int can_send_feed_img;
    QString constellation_name;
    QString pay_class_name;
    QString is_follow;
    QString famous_type;
    QString famous_type_title;
    QString famous_sub_type_title;
    QString job_title;
    int can_earn_money;
    int bonus_request_status;
    int gender;
    int is_first;
    int firstSoundRecord;
    int bindSina;
    int sound_count;
};

BEGIN_FROM_JSON(loginDetailsInfoEntity)
MEMBER_FROM_JSON(id)
MEMBER_FROM_JSON(phone)
MEMBER_FROM_JSON(email)
MEMBER_FROM_JSON(name)
MEMBER_FROM_JSON(access_token)
MEMBER_FROM_JSON(shareout_times)
MEMBER_FROM_JSON(language)
MEMBER_FROM_JSON(url)
MEMBER_FROM_JSON(link)
MEMBER_FROM_JSON(photo)
MEMBER_FROM_JSON(avatar_url)
MEMBER_FROM_JSON(signature)
MEMBER_FROM_JSON(followed_count)
MEMBER_FROM_JSON(last_login_ip)
MEMBER_FROM_JSON(last_login_time)
MEMBER_FROM_JSON(create_time)
MEMBER_FROM_JSON(create_ip)
MEMBER_FROM_JSON(email_key)
MEMBER_FROM_JSON(email_key_time)
MEMBER_FROM_JSON(status)
MEMBER_FROM_JSON(background)
MEMBER_FROM_JSON(theme)
MEMBER_FROM_JSON(homepage)
MEMBER_FROM_JSON(auto_tag)
MEMBER_FROM_JSON(activity_privacy)
MEMBER_FROM_JSON(activity_amount)
MEMBER_FROM_JSON(intro)
MEMBER_FROM_JSON(channel)
MEMBER_FROM_JSON(redirect)
MEMBER_FROM_JSON(source)
MEMBER_FROM_JSON(echo_webtag)
MEMBER_FROM_JSON(famous_status)
MEMBER_FROM_JSON(pay_expiry)
MEMBER_FROM_JSON(last_pay_time)
MEMBER_FROM_JSON(pay_status)
MEMBER_FROM_JSON(total_pay)
MEMBER_FROM_JSON(pay_class)
MEMBER_FROM_JSON(cash)
MEMBER_FROM_JSON(coins)
MEMBER_FROM_JSON(total_income)
MEMBER_FROM_JSON(total_withdrawal)
MEMBER_FROM_JSON(city)
MEMBER_FROM_JSON(constellation)
MEMBER_FROM_JSON(birthday)
MEMBER_FROM_JSON(last_pay_product)
MEMBER_FROM_JSON(can_send_feed)
MEMBER_FROM_JSON(can_down_img)
MEMBER_FROM_JSON(can_send_feed_img)
MEMBER_FROM_JSON(constellation_name)
MEMBER_FROM_JSON(pay_class_name)
MEMBER_FROM_JSON(is_follow)
MEMBER_FROM_JSON(famous_type)
MEMBER_FROM_JSON(famous_type_title)
MEMBER_FROM_JSON(famous_sub_type_title)
MEMBER_FROM_JSON(job_title)
MEMBER_FROM_JSON(can_earn_money)
MEMBER_FROM_JSON(bonus_request_status)
MEMBER_FROM_JSON(gender)
MEMBER_FROM_JSON(is_first)
MEMBER_FROM_JSON(firstSoundRecord)
MEMBER_FROM_JSON(bindSina)
MEMBER_FROM_JSON(sound_count)
END_FROM_JSON()

struct getTokenDetailsInfoEntity
{
    QString token;
};

BEGIN_FROM_JSON(getTokenDetailsInfoEntity)
MEMBER_FROM_JSON(token)
END_FROM_JSON()

#endif // ECHOWEBHTTPDATAENTITY_H
