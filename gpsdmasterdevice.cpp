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
        , _gpsdStarted(false)
{
  connect(_socket, SIGNAL( readyRead()), this, SLOT( readFromSocketAndCopy()));
  QByteArray hostname = qgetenv("GPSD_HOST");
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
  SlaveListT::iterator it;
  for( it=_slaves.begin(); it!=_slaves.end(); ++it)
  {
    if(it->second)
        it->first->seek(0);
  }
  while(_socket->canReadLine())
  {
    gotNewData = true;
    buf = _socket->readLine();
    for( it=_slaves.begin(); it!=_slaves.end(); ++it)
    {
      if(it->second)
          it->first->write(buf);
    }
  }
  if( gotNewData)
  {
    for( it=_slaves.begin(); it!=_slaves.end(); ++it)
    {
      if(it->second)
          it->first->seek(0);
    }
  }
}

bool GpsdMasterDevice::gpsdConnect()
{
  if( _socket->isOpen())
  {
#ifndef QT_NO_DEBUG
    qDebug() << "Already connected to gpsd";
#endif
    return true;
  }
  _socket->connectToHost(_hostname, _port);
  if( !_socket->isOpen())
  {
    qCritical() << "Could not open connection to gpsd";
    return false;
  }
  
#ifndef QT_NO_DEBUG
  qDebug() << "Connected to gpsd";
#endif
  return true;
}

void GpsdMasterDevice::gpsdDisconnect()
{
  if( !_socket->isOpen())
      return;
#ifndef QT_NO_DEBUG
  qDebug() << "Disconnecting from gpsd";
#endif
  _socket->close();
}

bool GpsdMasterDevice::gpsdStart()
{
  if(!_socket->isOpen())
      return false;
  
  if(!_gpsdStarted)
  {
#ifndef QT_NO_DEBUG
    qDebug() << "Starting gpsd";
#endif
    _socket->write("?WATCH={\"enable\":true, \"nmea\":true}\n");
    _gpsdStarted = true;
  }
  return true;
}

bool GpsdMasterDevice::gpsdStop()
{
  if(!_socket->isOpen())
      return false;
  
  if(_gpsdStarted)
  {
#ifndef QT_NO_DEBUG
    qDebug() << "Stopping gpsd";
#endif
    _socket->write("?WATCH={\"enable\": false}\n");
    _gpsdStarted = false;
  }
  return true;
}
 
QIODevice* GpsdMasterDevice::createSlave()
{
  if(!_slaves.size() && !gpsdConnect())
      return 0;
  QBuffer* slave = new QBuffer(this);
  slave->open(QIODevice::ReadWrite);
  _slaves.append(qMakePair(slave,false));
#ifndef QT_NO_DEBUG
  qDebug() << "Created slave" << slave;
#endif
  return slave;
}

void GpsdMasterDevice::destroySlave(QIODevice* slave)
{
  SlaveListT::iterator it = _slaves.begin();
  for(; it!=_slaves.end(); ++it)
  {
    if(it->first == slave)
    {
      _slaves.erase(it);
#ifndef QT_NO_DEBUG
      qDebug() << "Destroyed slave" << slave;
#endif
      delete slave;
      break;
    }
  }
  if(!_slaves.size())
  {
    gpsdStop();
    gpsdDisconnect();
  }
}

void GpsdMasterDevice::pauseSlave(QIODevice* slave)
{
  bool allPaused = true;
  SlaveListT::iterator it = _slaves.begin();
  for(; it!=_slaves.end(); ++it)
  {
    if(it->first == slave)
    {
#ifndef QT_NO_DEBUG
      qDebug() << "Pausing slave" << slave;
#endif
      it->second = false;
    }
    if(it->second)
        allPaused = false;
  }
  if(allPaused)
      gpsdStop();
}

void GpsdMasterDevice::unpauseSlave(QIODevice* slave)
{
  SlaveListT::iterator it = _slaves.begin();
  for(; it!=_slaves.end(); ++it)
  {
    if(it->first == slave)
    {
#ifndef QT_NO_DEBUG
      qDebug() << "Unpausing slave" << slave;
#endif
      it->second = true;
      gpsdStart();
      break;
    }
  }
}
