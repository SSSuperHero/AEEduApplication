#ifndef DEFINE_H
#define DEFINE_H
#include <QString>

#define             DEFINE_SCREEN_WIDTH                 1920.0
#define             DEFINE_SCREEN_HEIGHT                1080.0
#define             MINI_PLAYWIDGET_WIDTH               420.0
#define             MINI_PLAYWIDGET_HEIGHT              64.0
#define             LIST_WND_WIDTH                      380.0
#define             LIST_WND_HEIGHT                     450.0
#define             USER_WND_WIDTH                      230.0
#define             USER_WND_HEIGHT                     147.0
#define             LITTLE_PLAY_WIDGET_BEGIN_WIDTH      500.0
#define             LITTLE_PLAY_WIDGET_BEGIN_HEIGHT     90.0
#define             MAIN_WND_WIDTH                      1200.0
#define             MAIN_WND_HEIGHT                     720.0
#define             LOGGING_WND_WIDTH                   840.0
#define             LOGGING_WND_HEIGHT                  667.0

#define             PROMPT_WND_WIDTH                   177.0
#define             PROMPT_WND_HEIGHT                  40.0

#define             MAIN_LEFTWIDGET_WIDTH               84.0
#define             MAIN_LEFTWIDGET_HEIGHT              530.0
#define             MAIN_TITTLEWIDGET_HEIGHT            62.0
#define             MAIN_BOTTOMWIDGET_HEIGHT            70.0

#define             CONFIG_PATH                         "/Config.json"

#define             REBOOT_APPLICATION                  773

#define             WEB_ADDRESS_FRIST_PAGE              "http://www.google.com"

#define             ECHO_MEDIA_MAX_VOLUME_NUM           100

/////////////////////////////////////////release http/////////////////////////////////////////////////

#define             API_ADDRESS_HEADER                  "http://112.124.2.173/weeduTalk/index.php/"
#define             WEB_ADDRESS_LOGGING                 "components/users/wetalklogin/"


typedef enum MUESIC_PLAY_STATUS_
{
    MUESIC_PLAY_STOP = 0,
    MUESIC_PLAYING_START,
    MUESIC_PLAY_PAUSE,
    MUESIC_PLAY_NONE
}MUESIC_PLAY_STATUS;

enum WIDGET_SHOW_TYPE
{
    WIDGET_SHOW_MIN = 0,
    WIDGET_SHOW_NORMAL,
    WIDGET_SHOW_MAX,
    WIDGET_SHOW_MINE
};

#endif // DEFINE_H
