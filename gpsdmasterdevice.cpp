#include "gpsdmasterdevice.h"

#include <QTcpSocket>
#include <QBuffer>

GpsdMasterDevice* GpsdMasterDevice::_instance = 0;

GpsdMasterDevice* GpsdMasterDevice::instance()
{
  if(!_instance)
      _instance = new GpsdMasterDevice;
  return _instance;
}

GpsdMasterDevice::GpsdMasterDevice()
        : _socket( new QTcpSocket(this))
        , _hostname("localhost")
        , _port(2947)
{
  connect(_socket, SIGNAL( readyRead()), this, SLOT( readFromSocketAndCopy()));
  QByteArray hostname = qgetenv("GPSD_HOSTNAME");
  if( !hostname.isEmpty())
      _hostname = hostname;
  QByteArray port = qgetenv("GPSD_PORT");
  if( !port.isEmpty())
  {
    bool ok = false;
    uint tmp = port.toUInt(&ok);
    if(ok)
        _port = tmp;
  }
}

void GpsdMasterDevice::readFromSocketAndCopy()
{
  bool gotNewData = false;
  QByteArray buf;
  for( int i=0; i<_slaves.size(); ++i)
      _slaves[i]->seek(0);
  while(_socket->canReadLine())
  {
    gotNewData = true;
    buf = _socket->readLine();
    for( int i=0; i<_slaves.size(); ++i)
        _slaves[i]->write(buf);
  }
  if( gotNewData)
  {
    for( int i=0; i<_slaves.size(); ++i)
        _slaves[i]->seek(0);
  }
}

bool GpsdMasterDevice::gpsdConnect()
{
  if( _socket->isOpen())
  {
    qDebug() << "Already connected to gpsd";
    return true;
  }
  _socket->connectToHost(_hostname, _port);
  if( !_socket->isOpen())
  {
    qDebug() << "Could not open connection to gpsd";
    return false;
  }
  _socket->write("?WATCH={\"enable\":true, \"nmea\":true}\n");
  bool status = _socket->waitForReadyRead(1000);
  if( !status)
  {
    qDebug() << "No reply from gpsd";
    _socket->close();
    return false;
  }
  
  return true;
}

void GpsdMasterDevice::gpsdDisconnect()
{
  if( !_socket->isOpen())
      return;
  _socket->write("?WATCH={\"enable\": false}\n");
  _socket->close();
}

QIODevice* GpsdMasterDevice::createSlave()
{
  if(!_slaves.size())
      if(!gpsdConnect())
          return 0;
  QBuffer* slave = new QBuffer(this);
  slave->open(QIODevice::ReadWrite);
  _slaves.append(slave);
  return slave;
}

void GpsdMasterDevice::destroySlave(QIODevice* slave)
{
  if(_slaves.removeOne(slave))
      delete slave;
  if(!_slaves.size())
      gpsdDisconnect();
}
