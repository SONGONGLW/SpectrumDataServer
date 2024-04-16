#ifndef TCPCOMMONCLASS_H
#define TCPCOMMONCLASS_H

#include <QObject>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include "CreateDataThread.h"

class MyTcpServer : public QTcpServer {
    Q_OBJECT

public:
    MyTcpServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

signals:
    void SignalReceNewConnect(const QString &text);

private slots:
    void readData();
    void handleResults(const QByteArray &packet);

private:
    CreateDataThread *dataThread_ = nullptr;

    QList<QTcpSocket *> client_sockets_;

};

#endif // TCPCOMMONCLASS_H
