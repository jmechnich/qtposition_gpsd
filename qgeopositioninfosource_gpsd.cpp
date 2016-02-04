/*
  The MIT License (MIT)

  Copyright (c) 2016 Jörg Mechnich <joerg.mechnich@gmail.com>

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:
  
  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
