/*
 * Created on Sat Feb 25 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */

#include "ESP_32Builder.h"
#include <iostream>


namespace MaskUP
{
namespace Build
{

ESP_32Builder *ESP_32Builder::reset ()
{
    m_pEsp32 = ::MaskUP::Tools::make_unique <::MaskUP::Component::ESP_32> ();
    m_isReset = true;

    return this;
}

ESP_32Builder *ESP_32Builder::buildDeviceName(const std::string &inDeviceName)
{
    m_pEsp32->m_deviceName = inDeviceName;
    return this;
}

ESP_32Builder *ESP_32Builder::buildVersion(const std::string &inDeviceName)
{
    m_pEsp32->m_deviceName = inDeviceName;
    return this;
}

std::unique_ptr <::MaskUP::Component::ESP_32> ESP_32Builder::build ()
{
    if (m_isReset == true)
    {
        m_isReset = false;
        return std::move (m_pEsp32);
    }
    else
    {
        std::cout << "ESP32_Builder error : Cannot build ESP32.\n";
        return nullptr;
    }
}
}
}
