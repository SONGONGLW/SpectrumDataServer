#ifndef PARAMETERSETTINGDATACLASS_H
#define PARAMETERSETTINGDATACLASS_H

class ParameterSettingDataClass
{
public:
    ParameterSettingDataClass();

    ParameterSettingDataClass(const ParameterSettingDataClass &other);
    ParameterSettingDataClass(ParameterSettingDataClass &&other) noexcept;
    ParameterSettingDataClass &operator=(const ParameterSettingDataClass &other);
    ParameterSettingDataClass &operator=(ParameterSettingDataClass &&other) noexcept;

    void SetPointCount(const int point_count);
    void SetStartFrequency(const double start_frequency);
    void SetEndFrequency(const double end_frequency);
    int GetPointCount();
    double GetStartFrequency();
    double GetEndFrequency();

public:
    int point_count_;
    double start_frequency_;
    double end_frequency_;
};

#endif // PARAMETERSETTINGDATACLASS_H
