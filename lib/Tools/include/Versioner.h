/*
 * Created on Sat Jun 29 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUP
 */

#pragma once

#include <cstring>
#include <Arduino.h>
#include <string>

namespace MaskUP
{
namespace Tools
{


class Versioner
{
public:
    String getVersion();
    bool setVersion(const String& inVersion);
private:
    String m_major;
    String m_minor;
    String m_fix;

};
}
}