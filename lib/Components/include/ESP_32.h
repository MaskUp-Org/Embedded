/*
 * Created on Sat Feb 25 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */

#pragma once

#include <memory>
#include <string>
#include "Vibrator.h"
#include "BCHeadphone.h"
#include "ServoMotor.h"
#include "State.hpp"

namespace MaskUP
{
namespace Component
{

class ESP_32
{

public:
    ESP_32();
    std::string getDevicename();
    void setDevicename(const std::string &inDeviceName);


private:
    std::string m_deviceName;
    ::MaskUP::Enum::State m_state;



};

}
}