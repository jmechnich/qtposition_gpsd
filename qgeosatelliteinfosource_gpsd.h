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

#ifndef QGEOSATELLITEINFOSOURCE_GPSD_H
#define QGEOSATELLITEINFOSOURCE_GPSD_H

#include <QGeoSatelliteInfoSource>
#include <QMap>

class QIODevice;
class QTimer;

class QGeoSatelliteInfoSourceGpsd : public QGeoSatelliteInfoSource
{
  Q_OBJECT

public:
  explicit QGeoSatelliteInfoSourceGpsd(QObject* parent=0);
  ~QGeoSatelliteInfoSourceGpsd();
  
  Error error() const;
  int   minimumUpdateInterval() const;
  
public slots:
  void requestUpdate(int timeout=0);
  void startUpdates();
  void stopUpdates();

private slots:
  void tryReadLine();
  void reqTimerTimeout();
  
private:
  static const unsigned int ReqSatellitesInView = 0x1;
  static const unsigned int ReqSatellitesInUse  = 0x2;
  
  bool parseNmeaData(const char* data, int size);
  void readGSA(const char* data, int size);
  void readGSV(const char* data, int size);

  QIODevice* _device;
  QMap<int,QGeoSatelliteInfo> _satellitesInView;
  Error _lastError;
  bool _running;
  bool _wasRunning;
  unsigned int _reqDone;
  QTimer* _reqTimer;
};

#endif // QGEOSATELLITEINFOSOURCE_GPSD_H
