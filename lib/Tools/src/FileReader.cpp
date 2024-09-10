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

}
}