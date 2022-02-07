QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    acercade.cpp \
    finalizacion.cpp \
    main.cpp \
    producto.cpp \
    tienda.cpp

HEADERS += \
    acercade.h \
    finalizacion.h \
    producto.h \
    tienda.h

FORMS += \
    acercade.ui \
    finalizacion.ui \
    tienda.ui
TRANSLATIONS +=\
    Tienda_en.ts\
    Tienda_de.ts


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
