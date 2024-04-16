#include "SpectrumDataServer.h"
#include "ui_SpectrumDataServer.h"

#pragma execution_character_set("utf-8")

SpectrumDataServer::SpectrumDataServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SpectrumDataServer)
{
    ui->setupUi(this);

    InitUi();
    InitData();
    InitConnect();
}

SpectrumDataServer::~SpectrumDataServer()
{
    delete ui;
}

void SpectrumDataServer::InitUi()
{

}

void SpectrumDataServer::InitData()
{
    server = new MyTcpServer;

    SlotClickedListenButton(true);
    ui->btn_listen->setChecked(true);
}

void SpectrumDataServer::InitConnect()
{
    connect(ui->btn_listen, &QPushButton::clicked, this, &SpectrumDataServer::SlotClickedListenButton);
    connect(server, &MyTcpServer::SignalReceNewConnect, ui->textEdit, &QTextEdit::append);
}

void SpectrumDataServer::SlotClickedListenButton(bool checked)
{
    if(checked)
    {
        ui->btn_listen->setText("停止监听");
        if (!server->listen(QHostAddress(ui->lineEdit_ip->text()), ui->spinBox_port->value()))
        {
            ui->textEdit->append("Server could not start!");
        }
        ui->textEdit->append("Server started! " + server->serverAddress().toString() + ":" + QString::number(server->serverPort()));
    }
    else
    {
        ui->btn_listen->setText("开始监听");
        server->close();
        ui->textEdit->append("disconnect");
    }
}

