/*
 * Created on Sat Feb 25 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */

#pragma once

#include <memory>
#include <string>
#include "Enums.h"
#include "Versioner.h"

namespace MaskUP
{
namespace Component
{

class ESP_32
{

public:
    ESP_32();
    std::string getDeviceName();
    void setDeviceName(const std::string &inDeviceName);
    void setDeviceVersion(const std::string &inDeviceVersion);

    ::MaskUP::Enum::Component m_id;
    ::MaskUP::Enum::State m_state;

private:
    std::string m_deviceName;
    ::MaskUP::Tools::Versioner m_version;

};

}
}