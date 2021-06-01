QT       += core gui
QT += widgets
#

QT += charts
#requires(qtConfig(combobox))

#
CONFIG += c++11
#QT += printsupport
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    delete_window.cpp \
    file_data.cpp \
#    gist.cpp \
    gist.cpp \
    input_window.cpp \
    main.cpp \
    practic.cpp \
    search_window.cpp

HEADERS += \
    delete_window.h \
#    gist.h \
    gist.h \
    input_window.h \
    file_data.h \
    list.h \
    practic.h \
    search_window.h

FORMS += \
    practic.ui

# Default rules for deployment.]
#


#
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
