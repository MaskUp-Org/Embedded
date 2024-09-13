/*
 * Created on Fri Jun 28 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#include "Versioner.h"
#include <vector>

namespace MaskUP
{
namespace Tools
{

String Versioner::getVersion()
{
    String ret = "";
    ret = m_major + String(".")
        + m_minor + String(".")
        + m_fix;
    return ret;
}

std::vector <char*>split(const char* inStr, char* splitter)
{
    std::vector<char*> ret;
    ret.push_back(strtok(strdup(inStr), splitter));

    char* tmp = nullptr;
    while ((tmp = strtok(nullptr, splitter)) != nullptr)
    {
        ret.push_back(tmp);
    }
    return ret;
}

bool Versioner::setVersion(const String& inVersion)
{
    char* major = strtok(strdup(inVersion.c_str()), ".");
    char* minor = strtok(nullptr, ".");
    char* fix = strtok(nullptr, ".");

    if (major == nullptr || minor == nullptr || fix == nullptr)
    {
        return false;
    }
    else
    {
        m_major = major;
        m_minor = minor;
        m_fix = fix;
        return true;
    }
    return false;
}

}
}