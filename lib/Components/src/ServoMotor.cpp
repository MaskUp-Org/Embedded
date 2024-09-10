/*
 * Created on Mon Aug 26 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#include "ServoMotor.h"
#include "needed.hpp"
namespace MaskUP
{
namespace Component
{

ServoMotor::ServoMotor() :
    IComponent()
{

}

void ServoMotor::setup(const uint8_t inPin)
{
    // Servo tmp();
    // m_pServo = ::MaskUP::Tools::make_unique<Servo>();
    // m_pServo->attach(inPin);
    m_ready = true;
}

void ServoMotor::changePosition(const ::MaskUP::Enum::Position inPosition)
{
    // uint16_t direction = ::MaskUP::Enum::positionToDirection(inPosition);
    // m_pServo->write(direction);
    delay(1000);
}
}
}