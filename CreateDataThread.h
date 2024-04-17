#ifndef CREATEDATATHREAD_H
#define CREATEDATATHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "ParameterSettingDataClass.h"

class CreateDataThread : public QThread
{
    Q_OBJECT
public:
    explicit CreateDataThread(QObject *parent = nullptr);

    void generate_fourier_data(QString &data, int num_samples);
    void PackData(QByteArray &packet);
    void SetChangeParameter(const ParameterSettingDataClass &data);

signals:
      void SignalResultReady(const QByteArray &packet);

protected:
    void run() override;



private:
    ParameterSettingDataClass data_;


};

#endif // CREATEDATATHREAD_H
