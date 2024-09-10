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

ESP_32::ESP_32() :
    m_ready(true)
{
}

String ESP_32::getDeviceName()
{
    Serial.println("getDeviceName");
    return m_deviceName;
}
void ESP_32::setDeviceName(const String& inDeviceName)
{
    m_deviceName = inDeviceName;
    Serial.println("SetDeviceName");

}

String ESP_32::getDeviceVersion()
{
    Serial.println("getDeviceVersion");
    return m_version.getVersion();
}

void ESP_32::setDeviceVersion(const String& inDeviceVersion)
{
    Serial.println("SetDeviceVersion");
    m_version.setVersion(inDeviceVersion);
}
bool ESP_32::componentIsReady()
{
    return m_ready;
}
}
}