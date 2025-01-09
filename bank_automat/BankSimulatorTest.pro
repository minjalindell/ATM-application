QT       += core gui
QT += serialport
QT +=network
QT += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    balance.cpp \
    bankwindow.cpp \
    main.cpp \
    kortinlukija.cpp \
    otherwithdrawal.cpp \
    transactions.cpp \
    withdraw.cpp

HEADERS += \
    balance.h \
    bankwindow.h \
    kortinlukija.h \
    otherwithdrawal.h \
    transactions.h \
    withdraw.h

FORMS += \
    balance.ui \
    bankwindow.ui \
    kortinlukija.ui \
    otherwithdrawal.ui \
    transactions.ui \
    withdraw.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




RESOURCES += \
    Resources.qrc

win32: LIBS += -L$$PWD/../REST/build/debug/ -ldll-testi

INCLUDEPATH += $$PWD/../REST
DEPENDPATH += $$PWD/../REST

win32: LIBS += -L$$PWD/../RFID/build/debug/ -lkortinlukudll

INCLUDEPATH += $$PWD/../RFID
DEPENDPATH += $$PWD/../RFID

win32: LIBS += -L$$PWD/../pinUi/build/debug/ -lpinkoodi3DLL

INCLUDEPATH += $$PWD/../pinUi
DEPENDPATH += $$PWD/../pinUi
