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

std::ifstream getFile(const std::string& inFilePath)
{
    std::ifstream file(nullptr);
    file.open(inFilePath, std::fstream::in | std::fstream::out);
    return file;
}

std::string getDeviceInformation(const std::string& inDeviceInfo)
{
    std::string ret = "";
    std::ifstream file = getFile(inDeviceInfo);
    if (file.is_open()) {
        getline(file, ret);
        file.close();
    }
    return ret;
}

}
}