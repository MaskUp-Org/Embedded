/*
 * Created on Aug Tue 05 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */

#include "EmergencyButtonBuilder.h"
#include <iostream>
#include <Arduino.h>


namespace MaskUP
{
namespace Build
{

EmergencyButtonBuilder* EmergencyButtonBuilder::reset()
{
    m_pEmergencyButton = ::MaskUP::Tools::make_unique <::MaskUP::Communication::EmergencyButton>();
    m_isReset = true;

    return this;
}

EmergencyButtonBuilder* EmergencyButtonBuilder::setup(uint8_t inPin, uint8_t inMode)
{
    m_pEmergencyButton->setup(inPin, inMode);
    return this;
}

std::unique_ptr <::MaskUP::Communication::EmergencyButton> EmergencyButtonBuilder::build()
{
    if (m_isReset == true)
    {
        m_isReset = false;
        return std::move(m_pEmergencyButton);
    }
    else
    {
        std::cout << "EmergencyButtonBuilder error : Cannot build EmergencyButton.\n";
        return nullptr;
    }
}

}
}
