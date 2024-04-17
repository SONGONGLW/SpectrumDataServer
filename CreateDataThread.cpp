#include "CreateDataThread.h"

#include <random>
#include <QByteArray>

CreateDataThread::CreateDataThread(QObject *parent)
    :QThread(parent)
{

}

void CreateDataThread::run()
{
    while(true)
    {
        QByteArray packet;
        PackData(packet);
        emit SignalResultReady(packet);
    }
}

void CreateDataThread::generate_fourier_data(QString &data, int num_samples)
{
    // 添加噪声
    double start_value = -105;  // 起始值
    double end_value = -40;   // 目标值
    double noise_power = 5.0; // 噪声功率
    std::random_device rd;
    std::mt19937_64 gen(rd());

    num_samples = num_samples / 2;

    // 计算增长的比例
    double ratio = std::exp(std::log(end_value / start_value) / num_samples);
    // 初始化当前值为起始值
    double current_value = start_value;
    std::vector<double> noise;
    for(int i = 0; i < num_samples; ++i)
    {
        // 计算当前步的增长量，并更新当前值
        current_value *= ratio;
        std::normal_distribution<double> distribution(current_value, std::sqrt(noise_power));
        noise.push_back(distribution(gen));
    }

    // 获取noise序列的倒序
    std::vector<double> reversed_sequence(noise.rbegin(), noise.rend());

    // 合并序列
    noise.insert(noise.end(), reversed_sequence.begin(), reversed_sequence.end());

    // 生成频率和值的字符串
    double start_freq = data_.start_frequency_;
    double bili = (data_.end_frequency_ - start_freq) / data_.point_count_;
    for (int i = 0; i < noise.size(); ++i) {
        start_freq += bili;
        if (i != noise.size() - 1) {
            data += (QString::number(start_freq) + " " + QString::number(noise[i]) + " ");
        } else {
            data += (QString::number(start_freq) + " " + QString::number(noise[i]));
        }
    }
}

void CreateDataThread::PackData(QByteArray &packet)
{
    packet.clear();
    quint16 frame_header = 0x9198;
    QString data;
    generate_fourier_data(data, data_.point_count_);
    quint32 data_length = static_cast<quint32>(data.length());
    quint8 check = 0x69;
    quint16 frame_tail = 0x9298;

    packet.append(static_cast<quint8>(frame_header));
    packet.append(static_cast<quint8>(frame_header >> 8));
    packet.append(static_cast<quint8>(data_length));
    packet.append(static_cast<quint8>(data_length >> 8));
    packet.append(static_cast<quint8>(data_length >> 16));
    packet.append(static_cast<quint8>(data_length >> 24));
    packet.append(data);
    packet.append(check);
    packet.append(static_cast<quint8>(frame_tail));
    packet.append(static_cast<quint8>(frame_tail >> 8));
}

void CreateDataThread::SetChangeParameter(const ParameterSettingDataClass &data)
{
    data_ = data;
}
