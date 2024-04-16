QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CreateDataThread.cpp \
    TcpCommonClass.cpp \
    main.cpp \
    SpectrumDataServer.cpp

HEADERS += \
    CreateDataThread.h \
    SpectrumDataServer.h \
    TcpCommonClass.h

FORMS += \
    SpectrumDataServer.ui


BUILD_PATH = $${PWD}/build
CONFIG(debug, debug|release) {
    #debug
    LINUX_BUILD_PATH = "$${BUILD_PATH}/linux/debug/"
    #LINUX_BUILD_PATH = "/home/song/lws/$${TARGET}/build/linux/debug/"
    WINDOWS_BUILD_PATH = "$${BUILD_PATH}/windows/debug/"
} else {
    #release
    LINUX_BUILD_PATH = "$${BUILD_PATH}/linux/release/"
    #LINUX_BUILD_PATH = "/home/song/lws/$${TARGET}/build/linux/release/"
    WINDOWS_BUILD_PATH = "$${BUILD_PATH}/windows/release/"
}

win32{
#windows
    DESTDIR = $${WINDOWS_BUILD_PATH}/bin/
    OBJECTS_DIR = $${WINDOWS_BUILD_PATH}/tmp/obj
    MOC_DIR = $${WINDOWS_BUILD_PATH}/tmp/moc
    UI_DIR = $${WINDOWS_BUILD_PATH}/tmp/ui
    RCC_DIR = $${WINDOWS_BUILD_PATH}/tmp/source
    LIBS += -L$${WINDOWS_BUILD_PATH}/lib/
}else{
#linux
    DESTDIR = $${LINUX_BUILD_PATH}/bin/
    OBJECTS_DIR = $${LINUX_BUILD_PATH}/tmp/obj
    MOC_DIR = $${LINUX_BUILD_PATH}/tmp/moc
    UI_DIR = $${LINUX_BUILD_PATH}/tmp/ui
    RCC_DIR = $${LINUX_BUILD_PATH}/tmp/source
    LIBS += -L$${LINUX_BUILD_PATH}/bin/
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
