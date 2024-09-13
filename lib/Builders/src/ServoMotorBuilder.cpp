/*
 * Created on Sat Feb 25 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */

#include "ServoMotorBuilder.h"
#include <iostream>
#include <Arduino.h>
#include "FileReader.h"


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

ServoMotorBuilder* ServoMotorBuilder::setup()
{
    m_pServoMotor->setup();
    return this;
}


ServoMotorBuilder* ServoMotorBuilder::setFrequency()
{
    m_pServoMotor->setFrequency(::MaskUP::Enum::fromServomotorToInt(::MaskUP::Enum::Servomotor::SERVOFREQUENCY));
    return this;
}

ServoMotorBuilder* ServoMotorBuilder::setResolution()
{
    m_pServoMotor->setResolution(::MaskUP::Enum::fromServomotorToInt(::MaskUP::Enum::Servomotor::SERVORESOLUTION));

    return this;
}

ServoMotorBuilder* ServoMotorBuilder::setId()
{
    m_pServoMotor->setId(::MaskUP::Enum::fromServomotorToInt(::MaskUP::Enum::Servomotor::SERVOID));

    return this;
}

ServoMotorBuilder* ServoMotorBuilder::setPin()
{
    m_pServoMotor->setPin(::MaskUP::Enum::fromPinToInt(::MaskUP::Enum::Pin::SERVOMOTOR));

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
