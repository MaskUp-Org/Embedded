/*
 * Created on Fri Jun 28 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#include "JsonReader.h"
#include <Arduino.h>

namespace MaskUP
{
namespace Tools
{

void writeLog()
{
    return;
}

JsonReader::JsonReader(const std::string &inFileName) :
    m_fileName(inFileName) {}

JsonReader::~JsonReader() {}

// JsonDocument JsonReader::load()
// {
//     char *file;
//     std::ifstream istrm(m_fileName, std::ios::binary);
//     if (!istrm.is_open())
//         writeLog();
//     else
//     {
//         istrm.read(file, istrm.tellg());
//         deserializeJson(m_document, file);
//     }
//     return m_document;
// }
} // namespace MaskUP::Tools
} // namespace MaskUP::Tools