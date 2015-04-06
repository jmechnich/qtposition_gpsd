#include "qgeopositioninfosourcefactory_gpsd.h"

#include "qgeopositioninfosource_gpsd.h"
#include "qgeosatelliteinfosource_gpsd.h"

QGeoPositionInfoSource *QGeoPositionInfoSourceFactoryGpsd::positionInfoSource(QObject *parent)
{
  return new QGeoPositionInfoSourceGpsd(parent);
}

QGeoSatelliteInfoSource *QGeoPositionInfoSourceFactoryGpsd::satelliteInfoSource(QObject *parent)
{
  return new QGeoSatelliteInfoSourceGpsd(parent);
}

QGeoAreaMonitorSource *QGeoPositionInfoSourceFactoryGpsd::areaMonitor(QObject *parent)
{
  Q_UNUSED(parent);
  return 0;
}
