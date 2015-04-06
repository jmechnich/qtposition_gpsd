#ifndef QGEOPOSITIONINFOSOURCE_GPSD_H
#define QGEOPOSITIONINFOSOURCE_GPSD_H

#include <QNmeaPositionInfoSource>

class QGeoPositionInfoSourceGpsd : public QNmeaPositionInfoSource
{
  Q_OBJECT

public:
  explicit QGeoPositionInfoSourceGpsd(QObject* parent = 0);
  ~QGeoPositionInfoSourceGpsd();

public slots:
  void startUpdates();
  void stopUpdates();
  
private:
  QIODevice* _device;
  bool _running;
};

#endif // QGEOPOSITIONINFOSOURCE_GPSD_H
