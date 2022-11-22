TEMPLATE = app

QT += qml quick gui
CONFIG += c++11

SOURCES += \
    main.cpp \
    listener.cpp \
    email/client.cpp \
    email/base64.cpp \
    email/mySocket.cpp

RESOURCES += qml.qrc

win32 {
    LIBS += -lwsock32
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    listener.h \
    email/client.h \
    email/base64.h \
    email/mySocket.h

DISTFILES +=
