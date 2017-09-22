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
  int _timeout;

  static GpsdMasterDevice* _instance;
};

#endif // GPSDMASTERDEVICE_H
