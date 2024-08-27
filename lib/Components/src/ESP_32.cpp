/*
 * Created on Sat Feb 25 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */

#include "ESP_32.h"

namespace MaskUP
{
namespace Component
{

ESP_32::ESP_32() {
}

std::string ESP_32::getDeviceName ()
{
    return m_deviceName;
}
void ESP_32::setDevicename(const std::string &inDeviceName)
{
    m_deviceName = inDeviceName;
}
}
}