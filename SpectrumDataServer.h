#ifndef SPECTRUMDATASERVER_H
#define SPECTRUMDATASERVER_H

#include <QWidget>
#include "TcpCommonClass.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpectrumDataServer; }
QT_END_NAMESPACE

class SpectrumDataServer : public QWidget
{
    Q_OBJECT

public:
    SpectrumDataServer(QWidget *parent = nullptr);
    ~SpectrumDataServer();

private:
    void InitUi();
    void InitData();
    void InitConnect();

private slots:
    void SlotClickedListenButton(bool checked = false);

private:
    Ui::SpectrumDataServer *ui;

    MyTcpServer *server = nullptr;
};
#endif // SPECTRUMDATASERVER_H
