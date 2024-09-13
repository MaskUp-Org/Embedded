/*
 * Created on Mon Feb 26 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#include "BCHeadphone.h"
#include <iostream>

namespace MaskUP
{
namespace Component
{

void BCHeadphone::setup(uint8_t inPin, uint8_t inMode)
{
    Serial.println("Enter function : BCHeadphone::setup");
    (void)inPin;
    (void)inMode;
    Serial.println("Left function : BCHeadphone::setup");
}
void BCHeadphone::run()
{
    Serial.println("Enter function : BCHeadphone::run");
    std::cout << "BCHeadphone::run.\n";
    Serial.println("Left function : BCHeadphone::run");
}

void BCHeadphone::stop()
{
    Serial.println("Enter function : BCHeadphone::stop");
    std::cout << "BCHeadphone::stop.\n";
    Serial.println("Left function : BCHeadphone::stop");
}

void BCHeadphone::setSide(const ::MaskUP::Enum::Side inSide)
{
    Serial.println("Enter function : BCHeadphone::setSide");
    if (inSide != ::MaskUP::Enum::Side::END || inSide != ::MaskUP::Enum::Side::UNKNOWN)
    {
        m_side = inSide;
    }
    Serial.println("Left function : BCHeadphone::setSide");
}

}
}
