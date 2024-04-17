#include "ParameterSettingDataClass.h"

#include <utility>

ParameterSettingDataClass::ParameterSettingDataClass()
    : point_count_(3000)
    , start_frequency_(3000.00)
    , end_frequency_(6000.00)
{

}

ParameterSettingDataClass::ParameterSettingDataClass(const ParameterSettingDataClass &other)
{
    *this = other;
}

ParameterSettingDataClass::ParameterSettingDataClass(ParameterSettingDataClass &&other) noexcept
{
    *this = std::move(other);
}

ParameterSettingDataClass &ParameterSettingDataClass::operator=(const ParameterSettingDataClass &other)
{
    if(this != &other)
    {
        point_count_ = other.point_count_;
        start_frequency_ = other.start_frequency_;
        end_frequency_ = other.end_frequency_;
    }
    return *this;
}

ParameterSettingDataClass &ParameterSettingDataClass::operator=(ParameterSettingDataClass &&other) noexcept
{
    if(this != &other)
    {
        point_count_ = other.point_count_;
        start_frequency_ = other.start_frequency_;
        end_frequency_ = other.end_frequency_;

        other.point_count_ = 0;
        other.start_frequency_ = 0.00;
        other.end_frequency_ = 0.00;
    }
    return *this;
}

void ParameterSettingDataClass::SetPointCount(const int point_count)
{
    point_count_ = point_count;
}

void ParameterSettingDataClass::SetStartFrequency(const double start_frequency)
{
    start_frequency_ = start_frequency;
}

void ParameterSettingDataClass::SetEndFrequency(const double end_frequency)
{
    end_frequency_ = end_frequency;
}

int ParameterSettingDataClass::GetPointCount()
{
    return point_count_;
}

double ParameterSettingDataClass::GetStartFrequency()
{
    return start_frequency_;
}

double ParameterSettingDataClass::GetEndFrequency()
{
    return end_frequency_;
}
