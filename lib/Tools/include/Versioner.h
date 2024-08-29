/*
 * Created on Sat Jun 29 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUP
 */

#pragma once

#include <string>
#include <cstring>

namespace MaskUP
{
namespace Tools
{


class Versioner
{
public:
    std::string getVersion ();
    bool setVersion (const std::string &inVersion);
private:
    std::string m_major;
    std::string m_minor;
    std::string m_fix;

};
}
}