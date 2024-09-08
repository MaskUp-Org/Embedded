/*
 * Created on Sat Aug 17 2024
 *
 * Copyright (c) 2024 MaskUp
 */


#pragma once

#include <string>
#include <cstring>
#include <Arduino.h>
namespace MaskUP
{
namespace Enum
{
enum class Component
{
    UNKNOWN,
    ESP_32,
    LEFTBCHEADPHONE,
    RIGHTBCHEADPHONE,
    LEFTVIBRATOR,
    RIGHTVIBRATOR,
    EMERGENCYBUTTON,
    SERVOMOTOR,
    BATTERY,
    ALLVIBRATORS,
    BLUETOOTHMANAGER,

    END
};

inline Component fromStringToComponent(String inComponent)
{
    std::string tmp = strdup(inComponent.c_str());

    std::transform(tmp.begin(), tmp.end(), tmp.begin(), std::ptr_fun<int, int>(std::toupper));

    if (tmp == "ESP_32")
    {
        return ::MaskUP::Enum::Component::UNKNOWN;
    }
    else if (tmp == "LEFTVIBRATOR")
    {
        return ::MaskUP::Enum::Component::UNKNOWN;
    }
    else if (tmp == "RIGHTVIBRATOR")
    {
        return ::MaskUP::Enum::Component::UNKNOWN;
    }
    else if (tmp == "ALLVIBRATORS")
    {
        return ::MaskUP::Enum::Component::UNKNOWN;
    }
    else if (tmp == "EMERGENCYBUTTON")
    {
        return ::MaskUP::Enum::Component::UNKNOWN;
    }
    else if (tmp == "SERVOMOTOR")
    {
        return ::MaskUP::Enum::Component::UNKNOWN;
    }
    else if (tmp == "BLUETOOTHMANAGER")
    {
        return ::MaskUP::Enum::Component::BLUETOOTHMANAGER;
    }
    else if (tmp == "BATTERY")
    {
        return ::MaskUP::Enum::Component::UNKNOWN;
    }
    else if (tmp == "LEFTBCHEADPHONE")
    {
        return ::MaskUP::Enum::Component::UNKNOWN;
    }
    else if (tmp == "RIGHTBCHEADPHONE")
    {
        return ::MaskUP::Enum::Component::UNKNOWN;
    }
    return ::MaskUP::Enum::Component::UNKNOWN;
}
}
}