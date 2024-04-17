#include "TcpCommonClass.h"

#include <QTimer>

#pragma execution_character_set("utf-8")

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer(parent)
{
    dataThread_ = new CreateDataThread(this);
    connect(dataThread_, &CreateDataThread::finished, dataThread_, &QObject::deleteLater);
    connect(dataThread_, &CreateDataThread::SignalResultReady, this, &MyTcpServer::handleResults);
    dataThread_->start();
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    // 有新的连接请求时调用该函数
    QTcpSocket *clientSocket = new QTcpSocket(this);
    clientSocket->setSocketDescriptor(socketDescriptor);
    client_sockets_.push_back(clientSocket);

    connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::readData);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::disconnected, this, [&]{
        QTcpSocket *clientSocket_one = qobject_cast<QTcpSocket*>(sender());
        QString msg("客户端%1:%2连接断开");
        msg = msg.arg(clientSocket_one->peerAddress().toString())
                 .arg(clientSocket_one->peerPort());
        int index = client_sockets_.indexOf(clientSocket_one);
        if (index != -1)
        {
            client_sockets_[index] = nullptr;
            emit SignalReceNewConnect(msg);
        }
    });

    QString text("监听到服务器地址：%1:%2，客户端地址：%3:%4\n开始推送数据");
    text = text.arg(clientSocket->localAddress().toString())
            .arg(clientSocket->localPort())
            .arg(clientSocket->peerAddress().toString())
            .arg(clientSocket->peerPort());
    emit SignalReceNewConnect(text);
}

void MyTcpServer::readData()
{
    // 读取客户端发送的数据
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket)
        return;

    QByteArray data = clientSocket->readAll();

    emit SignalReceNewConnect(QString("接受到客户端消息：%1").arg(data.toStdString().c_str()));
    // 处理数据...
}

void MyTcpServer::handleResults(const QByteArray &packet)
{
    for(auto it = client_sockets_.begin(); it != client_sockets_.end();)
    {
        if((*it) == nullptr)
        {
            it = client_sockets_.erase(it);
        }
        else
        {
            (*it)->write(packet);
            ++it;
        }
    }
}

void MyTcpServer::SlotParameterChange(const ParameterSettingDataClass &data)
{
    dataThread_->SetChangeParameter(data);
}
