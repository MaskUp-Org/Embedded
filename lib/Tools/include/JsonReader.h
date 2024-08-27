/*
 * Created on Fri Jun 28 2024
 *
 * Copyright (c) 2024 Your Company
 */

#pragma once

// #include <ArduinoJson.h>
#include <fstream>
#include <string>


namespace MaskUP
{
namespace Tools
{

class JsonReader
{

public:
    // We wont create the json reader class without parameters.
    JsonReader(/* args */) = delete;
    JsonReader(const std::string &inFileName);
    ~JsonReader();
    // JsonDocument load();

private:
    const std::string m_fileName;
    // JsonDocument m_document;

};

}
}