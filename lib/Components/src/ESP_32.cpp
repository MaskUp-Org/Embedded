/*
 * Created on Sat Feb 25 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */

#include "ESP_32.h"
#include "FileReader.h"

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
    Serial.println("Enter function : ESP_32::getDeviceName");
    Serial.println("Left function : ESP_32::getDeviceName");
    return m_deviceName;
}
void ESP_32::setDeviceName(const String& inDeviceName)
{
    Serial.println("Enter function : ESP_32::setDeviceName");
    m_deviceName = inDeviceName;
    ::MaskUP::Tools::setDeviceName("/DeviceName", inDeviceName);
    Serial.println("Device name set to : " + inDeviceName);
    Serial.println("Left function : ESP_32::setDeviceName");

}

void ESP_32::resetDevice()
{
    Serial.println("Enter function : ESP_32::resetDevice");
    ::MaskUP::Tools::resetDeviceName();
    ::MaskUP::Tools::resetDeviceVersion();
    Serial.println("Left function : ESP_32::resetDevice");
}

String ESP_32::getDeviceVersion()
{
    Serial.println("Enter function : ESP_32::getDeviceVersion");
    Serial.println("Device version : " + m_version.getVersion());
    Serial.println("Left function : ESP_32::getDeviceVersion");
    return m_version.getVersion();
}

void ESP_32::setDeviceVersion(const String& inDeviceVersion)
{
    Serial.println("Enter function : ESP_32::setDeviceVersion");
    m_version.setVersion(inDeviceVersion);
    ::MaskUP::Tools::setDeviceVersion("/DeviceVersion", inDeviceVersion);
    Serial.println("Device version set to : " + inDeviceVersion);
    Serial.println("Left function : ESP_32::setDeviceVersion");
}
bool ESP_32::componentIsReady()
{
    return m_ready;
}
}
}