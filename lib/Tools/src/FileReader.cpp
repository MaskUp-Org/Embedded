/*
 * Created on Fri Sep 06 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUP
 */

#include "FileReader.h"

namespace MaskUP
{
namespace Tools
{

File getFile(const String& inFilePath)
{
    LittleFS.begin(true);
    File file = LittleFS.open(inFilePath.c_str(), "r+");
    //std::ifstream file(nullptr);
    //file.open(inFilePath, std::fstream::in | std::fstream::out);
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