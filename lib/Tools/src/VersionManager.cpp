/*
 * Created on Fri Jun 28 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#include "VersionManager.h"

namespace MaskUP
{
namespace Tools
{

std::string VersionManager::getVersion () 
{
    std::string ret;
    ret.append (m_major).append (".")
        .append (m_minor).append (".")
        .append (m_fix);
    return ret;
}

bool VersionManager::setVersion (const std::string &inVersion)
{
    char* major = strtok(strdup (inVersion.c_str()), ".");
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