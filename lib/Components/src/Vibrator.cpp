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
    m_ready = true;
}

void Vibrator::run()
{
    digitalWrite(m_pin, HIGH);
}

void Vibrator::stop()
{
    digitalWrite(m_pin, LOW);
}

void Vibrator::setSide(const ::MaskUP::Enum::Side inSide)
{
    if (inSide != ::MaskUP::Enum::Side::END || inSide != ::MaskUP::Enum::Side::UNKNOWN)
    {
        m_side = inSide;
    }
}

}
}