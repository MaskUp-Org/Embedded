/*
 * Created on Fri Sep 06 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUP
 */

#include "FileReader.h"
#include <string>
namespace MaskUP
{
namespace Tools
{

void initLittleSF() {
    if (!LittleFS.begin()) {
        throw std::runtime_error("LittleFS cannot begin.");
    }
    else {
        delay(500);
        Serial.println("LittleFS mounted successfully");
    }
}

File getFile(const String& inFilePath)
{
    File file = LittleFS.open(inFilePath.c_str(), "r+");
    if (!file)
    {
        LittleFS.end();
        std::string out = ("Could not open file", inFilePath.c_str());
        throw std::runtime_error(out);
    }
    return file;
}

File getFileWrite(const String& inFilePath)
{
    File file = LittleFS.open(inFilePath.c_str(), "w");
    if (!file)
    {
        LittleFS.end();
        std::string out = ("Could not open file", inFilePath.c_str());
        throw std::runtime_error(out);
    }
    return file;
}

String getDeviceInformation(const String& inDeviceInfo)
{
    String ret = "";
    File file = getFile(inDeviceInfo);
    if (file) {
        ret = file.readStringUntil('\n');
        file.close();
    }
    return ret;
}

void setDeviceName(const String& inDeviceInfo, const String& inData)
{
    String dataToWrite = "";
    if (inData.indexOf("MaskUp") != -1) {
        dataToWrite = inData;
    }
    else
    {
        dataToWrite = "MaskUp - " + inData;
    }
    File file = getFileWrite(inDeviceInfo);
    if (file) {
        file.print(dataToWrite);
        file.close();
    }
}

void setDeviceVersion(const String& inDeviceInfo, const String& inData)
{
    File file = getFileWrite(inDeviceInfo);
    if (file) {
        file.print(inData);
        file.close();
    }
}

void resetDeviceVersion()
{
    String inData = getDeviceInformation("/default/DeviceVersion");
    File file = getFileWrite("/DeviceVersion");
    if (file) {
        file.print(inData);
        file.close();
    }
}

void resetDeviceName()
{
    String inData = getDeviceInformation("/default/DeviceName");
    File file = getFileWrite("/DeviceName");
    if (file) {
        file.print(inData);
        file.close();
    }
}

}
}