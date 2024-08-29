/*
 * Created on Mon Aug 26 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#include "ServoMotor.h"

namespace MaskUP
{
namespace Component
{

void ServoMotor::setup (const uint8_t inPin)
{
    m_pServo->attach(inPin);
}

void ServoMotor::changePosition (const ::MaskUP::Enum::Position inPosition )
{
    uint16_t direction = ::MaskUP::Enum::positionToDirection (inPosition);
    m_pServo->write(direction);
    delay(1000);
}
}
}