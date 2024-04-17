#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>
#include "ParameterSettingDataClass.h"

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT
public:
    static SettingsForm& GetInstance(QWidget *parent = nullptr);
    void GetParameterData(ParameterSettingDataClass &data);
    void SetParameterData(const ParameterSettingDataClass &data);

signals:
    void SignalParameterChange(const ParameterSettingDataClass &data);

private slots:
    void SlotClickedSaveParameter();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    explicit SettingsForm(QWidget *parent = nullptr);
    ~SettingsForm();

    void InitConnect();

private:
    Ui::SettingsForm *ui;

    static SettingsForm *settings_form_;
};

#endif // SETTINGSFORM_H
