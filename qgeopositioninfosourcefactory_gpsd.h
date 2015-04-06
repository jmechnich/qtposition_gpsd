#ifndef QGEOPOSITIONINFOSOURCEFACTORY_GPSD_H
#define QGEOPOSITIONINFOSOURCEFACTORY_GPSD_H

#include <QObject>
#include <qgeopositioninfosourcefactory.h>

class QGeoPositionInfoSourceFactoryGpsd : public QObject, public QGeoPositionInfoSourceFactory
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "org.qt-project.qt.position.sourcefactory/5.0"
                      FILE "plugin.json")

    Q_INTERFACES(QGeoPositionInfoSourceFactory)

public:
    QGeoPositionInfoSource *positionInfoSource(QObject *parent);
    QGeoSatelliteInfoSource *satelliteInfoSource(QObject *parent);
    QGeoAreaMonitorSource *areaMonitor(QObject *parent);
};

#endif
