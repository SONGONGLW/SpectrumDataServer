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
    double noise_power = 5.0; // 噪声功率
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, std::sqrt(noise_power));
    std::vector<double> noise(num_samples);
    for (int i = 0; i < noise.size(); ++i) {
        noise[i] = distribution(gen) - 105.0;
    }

    // 指数级递增序列的起始值和终止值
    double start_value = -105.0;
    double end_value = -70.0;
    // 指数级递增序列的长度
    int num_points = 1200;
    // 生成从0到1的等间隔序列，作为指数函数的参数
    std::vector<double> x(num_points);
    for (int i = 0; i < num_points; ++i) {
        x[i] = static_cast<double>(i) / (num_points - 1);
    }
    // 计算指数级递增序列
    std::vector<double> exponential_sequence(num_points);
    for (int i = 0; i < num_points; ++i) {
        exponential_sequence[i] = start_value + (end_value - start_value) * std::exp(x[i]);
        exponential_sequence[i] += 70;
    }

    // 截取中间的2400个点
    std::vector<double> middle_noise(noise.begin() + 300, noise.begin() + 2700);

    // 将序列倒序
    std::vector<double> reversed_sequence(exponential_sequence.rbegin(), exponential_sequence.rend());

    // 合并序列
    exponential_sequence.insert(exponential_sequence.end(), reversed_sequence.begin(), reversed_sequence.end());

    // 将两个序列中的元素相加
    for (int i = 0; i < exponential_sequence.size(); ++i) {
        exponential_sequence[i] += middle_noise[i % 2400];
    }

    std::vector<double> frist_noise(noise.begin(), noise.begin() + 300);
    std::vector<double> last_noise(noise.end() - 300, noise.end());
    noise.clear();
    frist_noise.insert(frist_noise.end(), exponential_sequence.begin(), exponential_sequence.end());
    frist_noise.insert(frist_noise.end(), last_noise.begin(), last_noise.end());
    noise = frist_noise;

    // 生成频率和值的字符串
    double freq = 3000.0;
    for (int i = 0; i < noise.size(); ++i) {
        freq += 0.83;
        if (i != noise.size() - 1) {
            data += (QString::number(freq, 'f', 3) + " " + QString::number(noise[i], 'f', 3) + " ");
        } else {
            data += (QString::number(freq, 'f', 3) + " " + QString::number(noise[i], 'f', 3));
        }
    }
}

void CreateDataThread::PackData(QByteArray &packet)
{
    packet.clear();
    quint16 frame_header = 0x9198;
    QString data;
    generate_fourier_data(data, 3000);
    quint16 data_length = data.length();
    quint8 check = 0x69;
    quint16 frame_tail = 0x9298;

    packet.append(static_cast<quint8>(frame_header));
    packet.append(static_cast<quint8>(frame_header >> 8));
    packet.append(static_cast<quint8>(data_length));
    packet.append(static_cast<quint8>(data_length >> 8));
    packet.append(data);
    packet.append(check);
    packet.append(static_cast<quint8>(frame_tail));
    packet.append(static_cast<quint8>(frame_tail >> 8));
}
