#include "qgeopositioninfosource_gpsd.h"

#include "gpsdmasterdevice.h"

#include <QDebug>

QGeoPositionInfoSourceGpsd::QGeoPositionInfoSourceGpsd(QObject *parent)
        : QNmeaPositionInfoSource(QNmeaPositionInfoSource::RealTimeMode, parent)
        , _device(0)
        , _running(false)
{
  _device = GpsdMasterDevice::instance()->createSlave();
  setDevice(_device);
}

QGeoPositionInfoSourceGpsd::~QGeoPositionInfoSourceGpsd()
{
  if(_running)
      stopUpdates();
  GpsdMasterDevice::instance()->destroySlave(_device);
  _device = 0;
}

void QGeoPositionInfoSourceGpsd::startUpdates()
{
  if(!_running)
  {
    QNmeaPositionInfoSource::startUpdates();
    _running = true;
  }
}

void QGeoPositionInfoSourceGpsd::stopUpdates()
{
  if(_running)
  {
    QNmeaPositionInfoSource::stopUpdates();
    _running = false;
  }
}
