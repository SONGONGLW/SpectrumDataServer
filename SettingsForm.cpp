#include "SettingsForm.h"
#include "ui_SettingsForm.h"
#include <mutex>
#include <QKeyEvent>

SettingsForm* SettingsForm::settings_form_ = nullptr;
//std::mutex mutex_;

SettingsForm &SettingsForm::GetInstance(QWidget *parent)
{
//    std::lock_guard<std::mutex> lock(mutex_);
    if(!settings_form_)
    {
        settings_form_ = new SettingsForm(parent);
        settings_form_->setWindowTitle(QString::fromLocal8Bit("设置"));
        settings_form_->setWindowFlag(Qt::Tool);
        settings_form_->SetParameterData(ParameterSettingDataClass());
    }
    return *settings_form_;
}

void SettingsForm::GetParameterData(ParameterSettingDataClass &data)
{
    data.SetEndFrequency(ui->dspinBox_end_frequency->value());
    data.SetStartFrequency(ui->dspinBox_start_frequency->value());
    data.SetPointCount(ui->spinBox_point_count->value());
}

void SettingsForm::SetParameterData(const ParameterSettingDataClass &data)
{
    ui->spinBox_point_count->setValue(data.point_count_);
    ui->dspinBox_start_frequency->setValue(data.start_frequency_);
    ui->dspinBox_end_frequency->setValue(data.end_frequency_);
}

void SettingsForm::SlotClickedSaveParameter()
{
    ParameterSettingDataClass data;
    GetParameterData(data);
    emit SignalParameterChange(data);
}

void SettingsForm::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter)
    {
        SlotClickedSaveParameter();
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}

SettingsForm::SettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);

    qRegisterMetaType<ParameterSettingDataClass>("ParameterSettingDataClass");

    InitConnect();
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::InitConnect()
{
    connect(ui->btn_save, &QPushButton::clicked, this, &SettingsForm::SlotClickedSaveParameter);
}
