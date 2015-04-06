#ifndef GPSDMASTERDEVICE_H
#define GPSDMASTERDEVICE_H

#include <QObject>
#include <QList>

class QIODevice;
class QTcpSocket;

class GpsdMasterDevice : public QObject
{
  Q_OBJECT

public:
  static GpsdMasterDevice* instance();

  QIODevice* createSlave();
  void destroySlave(QIODevice* slave);

private slots:
  void readFromSocketAndCopy();
  
private:
  GpsdMasterDevice();
  bool gpsdConnect();
  void gpsdDisconnect();
  
  QList<QIODevice*> _slaves;
  QTcpSocket* _socket;
  QString _hostname;
  quint16 _port;
  
  static GpsdMasterDevice* _instance;
};

#endif // GPSDMASTERDEVICE_H
