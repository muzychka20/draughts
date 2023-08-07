QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AdditionalFunctions.cpp \
    board.cpp \
    changeparameters.cpp \
    checker.cpp \
    directionsstore.cpp \
    main.cpp \
    queen.cpp \
    style.cpp \
    widget.cpp

HEADERS += \
    AdditionalFunctions.h \
    board.h \
    changeparameters.h \
    checker.h \
    directionsstore.h \
    queen.h \
    style.h \
    widget.h

FORMS += \
    changeparameters.ui \
    widget.ui

win32 {
        RC_FILE += icon.rc
        OTHER_FILES += icon.rc
}

ICON = img/icon.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source.qrc
