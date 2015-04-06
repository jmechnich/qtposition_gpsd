#ifndef QGEOSATELLITEINFOSOURCE_GPSD_H
#define QGEOSATELLITEINFOSOURCE_GPSD_H

#include <QGeoSatelliteInfoSource>
#include <QMap>

class QIODevice;

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
  
private:
  bool parseNmeaData(const char* data, int size);
  void readGSA(const char* data, int size);
  void readGSV(const char* data, int size);

  QIODevice* _device;
  QMap<int,QGeoSatelliteInfo> _satellitesInView;
  Error _lastError;
  bool _running;
};

#endif // QGEOSATELLITEINFOSOURCE_GPSD_H
