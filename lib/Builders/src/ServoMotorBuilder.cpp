/*
 * Created on Sat Feb 25 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */

#include "ServoMotorBuilder.h"
#include <iostream>
#include <Arduino.h>


namespace MaskUP
{
namespace Build
{

ServoMotorBuilder* ServoMotorBuilder::reset()
{
    m_pServoMotor = ::MaskUP::Tools::make_unique <::MaskUP::Component::ServoMotor>();
    m_isReset = true;

    return this;
}

ServoMotorBuilder* ServoMotorBuilder::assignDefaultPosition(const ::MaskUP::Enum::Position inPosition)
{
    m_pServoMotor->changePosition(inPosition);
    return this;
}

std::unique_ptr <::MaskUP::Component::ServoMotor> ServoMotorBuilder::build()
{
    if (m_isReset == true)
    {
        m_isReset = false;
        return std::move(m_pServoMotor);
    }
    else
    {
        std::cout << "ESP32_Builder error : Cannot build ESP32.\n";
        return nullptr;
    }
}
}
}
