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
    String getDeviceName();
    void setDeviceName(const String& inDeviceName);
    void setDeviceVersion(const String& inDeviceVersion);

    ::MaskUP::Enum::Component m_id;
    ::MaskUP::Enum::State m_state;
    bool componentIsReady();

    bool m_ready = false;

private:
    String m_deviceName;
    ::MaskUP::Tools::Versioner m_version;

};

}
}