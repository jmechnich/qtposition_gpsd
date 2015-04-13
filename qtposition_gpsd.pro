TARGET = qtposition_gpsd
QT = core network positioning

TEMPLATE = lib
CONFIG += plugin

HEADERS += \
    gpsdmasterdevice.h \
    qgeopositioninfosource_gpsd.h \
    qgeopositioninfosourcefactory_gpsd.h \
    qgeosatelliteinfosource_gpsd.h

SOURCES += \
    gpsdmasterdevice.cpp \
    qgeopositioninfosource_gpsd.cpp \
    qgeopositioninfosourcefactory_gpsd.cpp \
    qgeosatelliteinfosource_gpsd.cpp

OTHER_FILES += plugin.json
