/*
 * Created on Mon Aug 26 2024:
 *
 * Copyright (c) 2024 MaskUP
 */

#include "ServoMotor.h"
#include "needed.hpp"
#include  "Enums.h"
namespace MaskUP
{
namespace Component
{

ServoMotor::ServoMotor() :
    IComponent()
{

}

void ServoMotor::setup()
{
    Serial.println("Enter function : ServoMotor::setup");
    ledcSetup(m_servoId, m_servoFrequency, m_servoResolution);
    ledcAttachPin(m_pin, m_servoId);
    m_ready = true;
    changePosition(::MaskUP::Enum::Position::M6000);
    Serial.println("Left function : ServoMotor::setup");
}

void ServoMotor::changePosition(const ::MaskUP::Enum::Position inPosition)
{
    Serial.println("Enter function : ServoMotor::changePosition");
    int pos = ::MaskUP::Enum::positionToDirection(inPosition);
    Serial.println("Position wanted : " + pos);
    ledcWrite(m_servoId, pos);
    Serial.println("Position set to " + pos);
    Serial.println("Left function : ServoMotor::changePosition");

    delay(2000);
}

::MaskUP::Enum::Position ServoMotor::getPosition()
{
    Serial.println("Enter function : ServoMotor::getPosition");
    Serial.println("Left function : ServoMotor::getPosition");
    return m_position;
}

void ServoMotor::setFrequency(const uint8_t inFrequency)
{
    Serial.println("Enter function : ServoMotor::setFrequency");
    m_servoFrequency = inFrequency;
    Serial.println("Left function : ServoMotor::setFrequency");
}

void ServoMotor::setResolution(const uint8_t inResolution)
{
    Serial.println("Enter function : ServoMotor::setResolution");
    m_servoResolution = inResolution;
    Serial.println("Left function : ServoMotor::setResolution");
}

void ServoMotor::setId(const uint8_t inId)
{
    Serial.println("Enter function : ServoMotor::setId");
    m_servoId = inId;
    Serial.println("Left function : ServoMotor::setId");
}

void ServoMotor::setPin(const uint8_t inPin)
{
    Serial.println("Enter function : ServoMotor::setPin");
    m_pin = inPin;
    Serial.println("Left function : ServoMotor::setPin");
}

}
}