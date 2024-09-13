/*
 * Created on Sat Jun 29 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUP
 */

#pragma once

#include <Arduino.h>
#include <iostream>
 //#include <fstream>
#include "LittleFS.h"
#include <string>

namespace MaskUP
{
namespace Tools
{

File getFile(const String& inFilePath);


/**
 * We works like that at MaskUP, you want an information about the device, you enter the filename (deviceName, deviceVersion...)
 */
String getDeviceInformation(const String& inDeviceInfo);

void setDeviceName(const String& inDeviceInfo, const String& inData);
void setDeviceVersion(const String& inDeviceInfo, const String& inData);

void resetDeviceName();
void resetDeviceVersion();

}
}