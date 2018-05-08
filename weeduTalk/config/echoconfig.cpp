#include "echoconfig.h"


const char* g_temp = "QScrollBar:vertical\
{\
        width:8px;\
        background:rgb(0,0,0,0%);\
        margin:0px,0px,0px,0px;\
        padding-top:12px;\
        padding-bottom:12px;\
        }\
        QScrollBar::handle:vertical\
{\
        width:8px;\
        background:rgb(0,0,0,25%);\
        border-radius:4px;\
        min-height:20px;\
        }\
        QScrollBar::handle:vertical:hover\
{\
        width:9px;\
        background:rgb(0,0,0,50%);\
        border-radius:4px;\
        min-height:20;\
        }\
        QScrollBar::add-line:vertical\
{\
        height:12px;\
        width:10px;\
        border-image:url(:/selectfile/scroll/3.png);\
        subcontrol-position:bottom;\
        }\
        QScrollBar::sub-line:vertical\
{\
        height:12px;\
        width:10px;\
        border-image:url(:/selectfile/scroll/1.png);\
        subcontrol-position:top;\
        }\
        QScrollBar::add-line:vertical:hover\
{\
        height:12px;\
        width:10px;\
        border-image:url(:/selectfile/scroll/4.png);\
        subcontrol-position:bottom;\
        }\
        QScrollBar::sub-line:vertical:hover\
{\
        height:12px;\
        width:10px;\
        border-image:url(:/selectfile/scroll/2.png);\
        subcontrol-position:top;\
        }\
        QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical\
{\
        background:rgb(0,0,0,6%);\
        border-radius:4px;\
}";

EchoConfig::EchoConfig()
{

}
