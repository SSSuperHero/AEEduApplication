#-------------------------------------------------
#
# Project created by QtCreator 2018-04-17T21:36:00
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += webenginewidgets

TARGET = weeduTalk
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

macx{

INCLUDEPATH += "$$PWD/QtAv/include"
LIBS += "-F$$PWD/QtAv/lib/"
LIBS += -framework QtAV

#INCLUDEPATH += "$$PWD/QtAv/lib/QtAVWidgets.framework/Headers"
LIBS += -framework QtAVWidgets

}

win32{

INCLUDEPATH += "$$PWD/QtAv/include"
LIBS += -L$$PWD/QtAv/lib/ -lQtAV1 -lQtAVWidgets1

}

macx: LIBS += -L$$PWD/zlib/lib/ -lz

INCLUDEPATH += $$PWD/zlib/include
DEPENDPATH += $$PWD/zlib/include

macx: PRE_TARGETDEPS += $$PWD/zlib/lib/libz.a

SOURCES += \
        main.cpp \
    weeduloginwidget.cpp \
    mgr/http/baseentity.cpp \
    mgr/http/echowebhttpapi.cpp \
    mgr/http/entitynetworkreplyholder.cpp \
    mgr/http/httpmgr.cpp \
    mgr/http/networkdownloadreplyholder.cpp \
    mgr/http/networkimagereplyholder.cpp \
    mgr/http/networkreplyholder.cpp \
    mgr/http/networkreplytimeout.cpp \
    utility/json.cpp \
    utility/jsonutil.cpp \
    utility/hashutility.cpp \
    utility/downloadutil.cpp \
    utility/pathutil.cpp \
    utility/stringutility.cpp \
    utility/tostringutil.cpp \
    utility/userinfo.cpp \
    utility/widget/imageutil.cpp \
    utility/widget/stylesheetutil.cpp \
    utility/widget/basemainwidget.cpp \
    utility/widget/basewidget.cpp \
    widgetmanager.cpp \
    utility/widget/frameless.cpp \
    config/configutil.cpp \
    weedumainwidget.cpp \
    weeduclassitem.cpp \
    weeduschoolunitwidget.cpp \
    weeduhighschoolunititem.cpp \
    weedumiddleschoolunititem.cpp \
    weeduprimaryschoolunititem.cpp \
    weedulessonitem.cpp \
    weeduchooselevelwidget.cpp \
    weeduschoolunititembase.cpp \
    utility/widget/windgetlabel.cpp \
    weeduhighschoollesson.cpp \
    weedulessonitembase.cpp \
    utility/widget/clicklabel.cpp \
    zlib/ioapi.c \
    zlib/unzip.c \
    zlib/zlibutility.cpp \
    utility/widget/downlodewidget.cpp \
    weedulessonguidewidget.cpp \
    weeduchooselevelitem.cpp \
    lessonRouter/weedulessonrouter.cpp \
    mgr/media/mediaplaymanager.cpp

HEADERS += \
    weeduloginwidget.h \
    mgr/http/baseentity.h \
    mgr/http/echowebhttpapi.h \
    mgr/http/entitynetworkreplyholder.h \
    mgr/http/httpmgr.h \
    mgr/http/networkdownloadreplyholder.h \
    mgr/http/networkimagereplyholder.h \
    mgr/http/networkreplyholder.h \
    mgr/http/networkreplytimeout.h \
    mgr/http/module/echohttpinfoentity.h \
    mgr/http/module/echosearchallentity.h \
    mgr/http/module/echowebhttpdataentity.h \
    utility/json.h \
    utility/jsonutil.h \
    mybasesingleton.h \
    config/define.h \
    utility/hashutility.h \
    utility/callonce.h \
    utility/downloadutil.h \
    utility/pathutil.h \
    utility/singleton.h \
    utility/singletonmgrbase.h \
    utility/stringutility.h \
    utility/tostringutil.h \
    utility/userinfo.h \
    utility/widget/imageutil.h \
    utility/widget/stylesheetutil.h \
    utility/widget/basemainwidget.h \
    utility/widget/basewidget.h \
    widgetmanager.h \
    utility/widget/frameless.h \
    config/configutil.h \
    weedumainwidget.h \
    weeduclassitem.h \
    weeduschoolunitwidget.h \
    weeduhighschoolunititem.h \
    weedumiddleschoolunititem.h \
    weeduprimaryschoolunititem.h \
    weedulessonitem.h \
    weeduchooselevelwidget.h \
    weeduschoolunititembase.h \
    utility/widget/windgetlabel.h \
    weeduhighschoollesson.h \
    weedulessonitembase.h \
    utility/widget/clicklabel.h \
    zlib/ioapi.h \
    zlib/unzip.h \
    zlib/zlibutility.h \
    utility/widget/downlodewidget.h \
    weedulessonguidewidget.h \
    weeduchooselevelitem.h \
    lessonRouter/weedulessonrouter.h \
    mgr/media/mediaplaymanager.h

FORMS += \
    weeduloginwidget.ui \
    weedumainwidget.ui \
    weeduclassitem.ui \
    weeduschoolunitwidget.ui \
    weeduhighschoolunititem.ui \
    weedumiddleschoolunititem.ui \
    weeduprimaryschoolunititem.ui \
    weedulessonitem.ui \
    weeduchooselevelwidget.ui \
    weeduhighschoollesson.ui \
    utility/widget/downlodewidget.ui \
    weedulessonguidewidget.ui \
    weeduchooselevelitem.ui

RESOURCES += \
    resource.qrc
