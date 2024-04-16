#include "SpectrumDataServer.h"

#include <QApplication>

#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpectrumDataServer w;
    w.setWindowTitle("电磁频谱数据模拟器 v1.0.0.1");
    w.show();
    return a.exec();
}
