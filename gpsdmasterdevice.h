#ifndef GPSDMASTERDEVICE_H
#define GPSDMASTERDEVICE_H

#include <QObject>
#include <QList>
#include <QPair>

class QIODevice;
class QTcpSocket;

class GpsdMasterDevice : public QObject
{
  Q_OBJECT

public:
  static GpsdMasterDevice* instance();

  QIODevice* createSlave();
  void destroySlave(QIODevice* slave);
  void pauseSlave(QIODevice* slave);
  void unpauseSlave(QIODevice* slave);

private slots:
  void readFromSocketAndCopy();
  
private:
  GpsdMasterDevice();
  bool gpsdConnect();
  void gpsdDisconnect();
  bool gpsdStart();
  bool gpsdStop();
  
  typedef QList<QPair<QIODevice*,bool> > SlaveListT;
  
  SlaveListT _slaves;
  QTcpSocket* _socket;
  QString _hostname;
  quint16 _port;
  bool _gpsdStarted;
  
  static GpsdMasterDevice* _instance;
};

#endif // GPSDMASTERDEVICE_H
