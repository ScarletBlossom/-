QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


RC_ICONS = favicon.ico
DESTDIR = ./bin


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clickedlabel.cpp \
    global.cpp \
    httpmgr.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    register.cpp \
    resetpw.cpp \
    tcpmgr.cpp \
    timerbtn.cpp

HEADERS += \
    clickedlabel.h \
    global.h \
    httpmgr.h \
    login.h \
    mainwindow.h \
    register.h \
    resetpw.h \
    singleton.h \
    tcpmgr.h \
    timerbtn.h

FORMS += \
    login.ui \
    mainwindow.ui \
    register.ui \
    resetpw.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rc.qrc

DISTFILES += \
    config.ini \
    res/images/chat_icon_select_press.png \
    res/images/close_search.png \
    res/images/close_transparent.png \
    res/images/contact_list.png \
    res/images/contact_list_hover.png \
    res/images/contact_list_press.png \
    res/images/favicon.ico \
    res/images/female.png \
    res/images/filedir.png \
    res/images/filedir_hover.png \
    res/images/filedir_press.png \
    res/images/head_1.jpg \
    res/images/head_2.jpg \
    res/images/head_3.jpg \
    res/images/head_4.jpg \
    res/images/head_5.jpg \
    res/images/ice.png \
    res/images/instagram-image1.jpg \
    res/images/instagram-image2.jpg \
    res/images/instagram-image3.jpg \
    res/images/instagram-image4.jpg \
    res/images/instagram-image5.jpg \
    res/images/loading.gif \
    res/images/male.png \
    res/images/msg_chat_hover.png \
    res/images/msg_chat_normal.png \
    res/images/msg_chat_press.png \
    res/images/profile-image.jpg \
    res/images/red_point.png \
    res/images/right_tip.png \
    res/images/search.png \
    res/images/settings.png \
    res/images/settings_hover.png \
    res/images/settings_press.png \
    res/images/settings_select_hover.png \
    res/images/settings_select_press.png \
    res/images/smile.png \
    res/images/smile_hover.png \
    res/images/smile_press.png \
    res/images/tipclose.png \
    res/images/unvisible.png \
    res/images/unvisible_hover.png \
    res/images/video_chat_hover.png \
    res/images/video_chat_normal.png \
    res/images/video_chat_press.png \
    res/images/visible.png \
    res/images/visible_hover.png \
    res/images/voice_chat_hover.png \
    res/images/voice_chat_normal.png \
    res/images/voice_chat_press.png

win32:CONFIG(release, debug | release)
{
    #指定要拷贝的文件目录为工程目录下release目录下的所有dll、lib文件，例如工程目录在D:\QT\Test
    #PWD就为D:/QT/Test，DllFile = D:/QT/Test/release/*.dll
    TargetConfig = $${PWD}/config.ini
    #将输入目录中的"/"替换为"\"
    TargetConfig = $$replace(TargetConfig, /, \\)
    #将输出目录中的"/"替换为"\"
    OutputDir =  $${OUT_PWD}/$${DESTDIR}
    OutputDir = $$replace(OutputDir, /, \\)
    //执行copy命令
    QMAKE_POST_LINK += copy /Y \"$$TargetConfig\" \"$$OutputDir\"
}

