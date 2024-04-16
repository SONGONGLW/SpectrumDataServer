#ifndef CREATEDATATHREAD_H
#define CREATEDATATHREAD_H

#include <QThread>
#include <QTcpSocket>

class CreateDataThread : public QThread
{
    Q_OBJECT
public:
    explicit CreateDataThread(QObject *parent = nullptr);

    void generate_fourier_data(QString &data, int num_samples);
    void PackData(QByteArray &packet);

signals:
      void SignalResultReady(const QByteArray &packet);

protected:
    void run() override;



private:

};

#endif // CREATEDATATHREAD_H
