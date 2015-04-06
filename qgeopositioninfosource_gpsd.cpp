#include "qgeopositioninfosource_gpsd.h"

#include "gpsdmasterdevice.h"

#include <QDebug>

QGeoPositionInfoSourceGpsd::QGeoPositionInfoSourceGpsd(QObject *parent)
        : QNmeaPositionInfoSource(QNmeaPositionInfoSource::RealTimeMode, parent)
        , _device(0)
        , _running(false)
{}

QGeoPositionInfoSourceGpsd::~QGeoPositionInfoSourceGpsd()
{
  if(_running)
      stopUpdates();
}

void QGeoPositionInfoSourceGpsd::startUpdates()
{
  if(!_running)
  {
    _device = GpsdMasterDevice::instance()->createSlave();
    setDevice( _device);
    QNmeaPositionInfoSource::startUpdates();
    _running = true;
  }
}

void QGeoPositionInfoSourceGpsd::stopUpdates()
{
  if(_running)
  {
    QNmeaPositionInfoSource::stopUpdates();
    setDevice(0);
    GpsdMasterDevice::instance()->destroySlave(_device);
    _device = 0;
    _running = false;
  }
}
