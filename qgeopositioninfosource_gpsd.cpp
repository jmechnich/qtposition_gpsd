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
    GpsdMasterDevice::instance()->unpauseSlave(_device);
    QNmeaPositionInfoSource::startUpdates();
    _running = true;
  }
}

void QGeoPositionInfoSourceGpsd::stopUpdates()
{
  if(_running)
  {
    QNmeaPositionInfoSource::stopUpdates();
    GpsdMasterDevice::instance()->pauseSlave(_device);
    _running = false;
  }
}
