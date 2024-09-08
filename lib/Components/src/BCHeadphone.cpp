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
    (void)inPin;
    (void)inMode;
    std::cout << "BCHeadphone::run.\n";
}
void BCHeadphone::run()
{
    std::cout << "BCHeadphone::run.\n";
}

void BCHeadphone::stop()
{
    std::cout << "BCHeadphone::stop.\n";
}

void BCHeadphone::setSide(const ::MaskUP::Enum::Side inSide)
{
    if (inSide != ::MaskUP::Enum::Side::END || inSide != ::MaskUP::Enum::Side::UNKNOWN)
    {
        m_side = inSide;
    }
}

}
}
