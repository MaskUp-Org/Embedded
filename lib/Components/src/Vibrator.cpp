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

void Vibrator::setup (uint8_t inPin, uint8_t inMode)
{
    pinMode(inPin, inMode);
}

void Vibrator::run ()
{
    // m_state = true;
    std::cout << "Vibrator::run.\n";
}

void Vibrator::stop ()
{
    // m_state = false;
    std::cout << "Vibrator::stop.\n";
}

}
}