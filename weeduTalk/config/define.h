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
                            /***************************debug***********************/
#define             API_TEST_ADDRESS_HEADER              "http://34.staging-api.app-echo.com"
                            /***************************release***********************/
#define             API_ADDRESS_HEADER                  "http://112.124.2.173/weeduTalk/index.php/"
#define             WEB_ADDRESS_HEADER                  "http://www.app-echo.com"
#define             WEB_TEST_ADDRESS_HEADER             "http://34.staging-web.app-echo.com"

#define             WEB_ADDRESS_WEI_BO                  "/index/open-login?platform=sina"
#define             WEB_ADDRESS_WEI_XIN                 "/index/open-login?platform=wechat"

#define             WEB_ADDRESS_REGISTER                "/user/pc-reg"
#define             WEB_ADDRESS_FORGET                  "/user/pc-forget-pwd"
#define             WEB_ADDRESS_SEARCH                  "/pc/search/all"
#define             WEB_ADDRESS_GET_TOKEN               "/user/get-sso-token"
#define             WEB_ADDRESS_SOUND_INFO              "/sound/info"
#define             WEB_ADDRESS_MAIN                    "/pc/sound/index?page=1"
#define             WEB_ADDRESS_LOGGING                 "components/users/wetalklogin/"
#define             WEB_ADDRESS_OPEN_LOGGING            "/index/open-login"
#define             WEB_ADDRESS_LOGGING_OUT             "/index/logout"
#define             WEB_ADDRESS_UPDATE_APP              "/system/echo-version"

#define             WEB_ADDRESS_FA_BU                   "/pc/#!/sound/upload"
#define             WEB_ADDRESS_HUI_YUAN                "/pc/#!/pay/membership"
#define             WEB_ADDRESS_GOLD                    "/pc/#!/pay/coins"
#define             WEB_ADDRESS_EDIT_USER_INFO          "/pc/#!/user/edit"
#define             WEB_ADDRESS_SEARCH_RES              "/pc/#!/search?type=1&keyword="
#define             WEB_ADDRESS_BELL                    "/pc/#!/bell"
#define             WEB_ADDRESS_BELL_BUYED              "/pc/#!/bell/buyed"
#define             WEB_ADDRESS_BELL_MY_MAKE            "/pc/#!/bell/mine"
#define             WEB_ADDRESS_MV_INFO                 "/pc/#!/mv/info/"
#define             WEB_ADDRESS_TUI_JIAN                "/pc/#!/"
#define             WEB_ADDRESS_SOUND_INFO_ALL          "/pc/#!/sound/info/"
#define             WEB_ADDRESS_BELL_INFO               "/pc/#!/search?type=4&keyword="
#define             WEB_ADDRESS_PIN_DAO                 "/pc/#!/channel"
#define             WEB_ADDRESS_SHI_PIN                 "/pc/#!/mv"

#define             WEB_ADDRESS_SOUND_LIKE_LIST         "/player/likes"
#define             WEB_ADDRESS_SOUND_OFFLINE_LIST      "/player/offline"
#define             WEB_ADDRESS_SOUND_INFO_IDS          "/sound/info-ids"
#define             WEB_ADDRESS_SOUND_LIKE_OR_UNLIKE    "/sound/like"
#define             WEB_ADDRESS_SOUND_REMOVE            "/player/offline-remove"

#define             WEB_ADDRESS_GET_UPLOAD_TOKEN        "/index/get-upload-token"
#define             WEB_ADDRESS_BELL_MAKE_SAVE          "/bells/add"
#define             WEB_ADDRESS_BELL_EDIT_SAVE          "/bells/add-edit-log"
#define             WEB_ADDRESS_BELL_EDIT_INFO_GET      "/bells/edit-log-info"
#define             WEB_ADDRESS_GET_BELL_BY_SOUNDID     "/bells/info"
#define             WEB_ADDRESS_BELL_DOWNLOAD           "/bells/download"
#define             WEB_ADDRESS_BELL_ISBUY              "/bells/is-buy"
#define             WEB_ADDRESS_BELL_TRY_LISTEN         "/bells/try-listen"
#define             WEB_ADDRESS_USER_COINS              "/user/coins"
#define             WEB_ADDRESS_PAY_BUY                 "/pay/buy"

typedef enum WEB_PAGE_TYPE_
{
    TUI_JIAN_PAGE,
    PING_DAO_PAGE,
    SHI_PIN_PAGE,
    SHI_PIN_INFO_PAGE,
    LING_SHENG_PAGE,
    BELL_MANAGE,
    BELL_MY_MAKE,
    FA_BU_PAGE,
    SOUND_INFO_PAGE,
    HUI_YUAN_PAGE,
    GOLD_PAGE,
    EDIT_USER_INFO_PAGE,
    SEARCH_INDEX_PAGE,
    SEARCH_PAGE
}WEB_PAGE_TYPE;

typedef enum MUESIC_PLAY_STATUS_
{
    MUESIC_PLAY_STOP = 0,
    MUESIC_PLAYING_START,
    MUESIC_PLAY_PAUSE,
    MUESIC_PLAY_NONE
}MUESIC_PLAY_STATUS;

typedef enum PLAY_STATUES_
{
    UN_PLAYING,
    PLAYING_MUESIC,
    PLAYING_MV,
}PLAY_STATUES;

typedef enum CURRING_PLAY_TYPE_{
    PLAYING_MUESIC_LOOP_ALL,
    PLAYING_MUESIC_LOOP_ONE,
    PLAYING_MUESIC_RANDOM
}CURRING_PLAY_TYPE;

enum WIDGET_SHOW_TYPE
{
    WIDGET_SHOW_MIN = 0,
    WIDGET_SHOW_NORMAL,
    WIDGET_SHOW_MAX,
    WIDGET_SHOW_MINE
};

enum WEB_LOGIN_TYPE
{
    WEB_LOGIN_FIRST = 0,
    WEB_LOGIN_SECOND,
    WEB_LOGIN_THIRD
};

#endif // DEFINE_H
