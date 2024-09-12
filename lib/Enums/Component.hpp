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

enum class Servomotor : int
{
    UNKNOWN = 1000,

    SERVOID = 1,
    SERVOFREQUENCY = 50,
    SERVORESOLUTION = 12,

    END = 1001
};

inline int fromServomotorToInt(const Servomotor inServo)
{
    return static_cast<int> (inServo);
}

inline Component fromStringToComponent(String inComponent)
{
    std::string tmp = strdup(inComponent.c_str());

    std::transform(tmp.begin(), tmp.end(), tmp.begin(), std::ptr_fun<int, int>(std::toupper));

    if (tmp == "ESP_32")
    {
        return ::MaskUP::Enum::Component::ESP_32;
    }
    else if (tmp == "LEFTVIBRATOR")
    {
        return ::MaskUP::Enum::Component::LEFTVIBRATOR;
    }
    else if (tmp == "RIGHTVIBRATOR")
    {
        return ::MaskUP::Enum::Component::RIGHTVIBRATOR;
    }
    else if (tmp == "ALLVIBRATORS")
    {
        return ::MaskUP::Enum::Component::ALLVIBRATORS;
    }
    else if (tmp == "EMERGENCYBUTTON")
    {
        return ::MaskUP::Enum::Component::EMERGENCYBUTTON;
    }
    else if (tmp == "SERVOMOTOR")
    {
        return ::MaskUP::Enum::Component::SERVOMOTOR;
    }
    else if (tmp == "BLUETOOTHMANAGER")
    {
        return ::MaskUP::Enum::Component::BLUETOOTHMANAGER;
    }
    else if (tmp == "BATTERY")
    {
        return ::MaskUP::Enum::Component::BATTERY;
    }
    else if (tmp == "LEFTBCHEADPHONE")
    {
        return ::MaskUP::Enum::Component::LEFTBCHEADPHONE;
    }
    else if (tmp == "RIGHTBCHEADPHONE")
    {
        return ::MaskUP::Enum::Component::RIGHTBCHEADPHONE;
    }
    return ::MaskUP::Enum::Component::UNKNOWN;
}

inline String fromComponentToString(const Component inComponent)
{
    switch (inComponent)
    {
    case Component::UNKNOWN:
        return "UNKNOWN";
    case Component::ALLVIBRATORS:
        return "ALLVIBRATORS";
    case Component::BATTERY:
        return "BATTERY";
    case Component::BLUETOOTHMANAGER:
        return "BLUETOOTHMANAGER";
    case Component::EMERGENCYBUTTON:
        return "EMERGENCYBUTTON";
    case Component::ESP_32:
        return "ESP_32";
    case Component::LEFTBCHEADPHONE:
        return "LEFTBCHEADPHONE";
    case Component::LEFTVIBRATOR:
        return "LEFTVIBRATOR";
    case Component::RIGHTBCHEADPHONE:
        return "RIGHTBCHEADPHONE";
    case Component::RIGHTVIBRATOR:
        return "RIGHTVIBRATOR";
    case Component::SERVOMOTOR:
        return "SERVOMOTOR";
    case Component::END:
    default:
        return "END";

    }
}
}
}