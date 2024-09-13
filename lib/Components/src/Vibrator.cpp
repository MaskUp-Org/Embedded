/*
 * Created on Mon Feb 26 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#include "Vibrator.h"
#include <iostream>

namespace MaskUP
{
namespace Component
{

Vibrator::Vibrator() :
    IComponent(),
    m_pin(0)
{
}

void Vibrator::setup(uint8_t inPin, uint8_t inMode)
{
    pinMode(inPin, inMode);
    m_pin = inPin;
    run();
    delay(500);
    stop();
    m_ready = true;
}

void Vibrator::run()
{
    Serial.println("Enter function : Vibrator::run");
    digitalWrite(m_pin, LOW);
    Serial.println("Left function : Vibrator::run");
}

void Vibrator::stop()
{
    Serial.println("Enter function : Vibrator::stop");
    digitalWrite(m_pin, HIGH);
    Serial.println("Left function : Vibrator::stop");
}

void Vibrator::setSide(const ::MaskUP::Enum::Side inSide)
{
    Serial.println("Enter function : Vibrator::setSide");
    if (inSide != ::MaskUP::Enum::Side::END || inSide != ::MaskUP::Enum::Side::UNKNOWN)
    {
        m_side = inSide;
        Serial.println("Vibrator Side set to : " + ::MaskUP::Enum::fromSideToString(inSide));
    }
    Serial.println("Left function : Vibrator::setSide");
}

}
}