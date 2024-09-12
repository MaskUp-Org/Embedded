/*
 * Created on Sat Aug 17 2024
 *
 * Copyright (c) 2024 Your Company
 */

#pragma once

#include <Arduino.h>
namespace MaskUP
{
namespace Enum
{

enum class Type {
    UNKNOWN,
    COMMAND,
    QUERY,

    END
};

enum class Action {
    UNKNOWN,
    SET_ALTITUDE,
    DIRECTION,
    SET_VERSION,
    STOP_SOUND,
    RUN_SOUND,
    SET_DEVICE_NAME,
    GET_DEVICE_NAME,
    GET_VERSION,
    GET_ALTITUDE,
    GET_BATTERY_PERCENTAGE,
    RESET,


    END
};

inline Action actionFromString(const String& inAction)
{
    if (inAction == "SET_ALTITUDE")
        return Action::SET_ALTITUDE;
    else if (inAction == "DIRECTION")
        return Action::DIRECTION;
    else if (inAction == "GET_BATTERY")
        return Action::GET_BATTERY_PERCENTAGE;
    else if (inAction == "GET_ALTITUDE")
        return Action::GET_ALTITUDE;
    else if (inAction == "SET_VERSION")
        return Action::SET_VERSION;
    else if (inAction == "STOP_SOUND")
        return Action::STOP_SOUND;
    else if (inAction == "RUN_SOUND")
        return Action::RUN_SOUND;
    else if (inAction == "SET_DEVICE_NAME")
        return Action::SET_DEVICE_NAME;
    else if (inAction == "GET_DEVICE_NAME")
        return Action::GET_DEVICE_NAME;
    else if (inAction == "GET_VERSION")
        return Action::GET_VERSION;

    else
        Serial.println("Action = -" + inAction + "--");
    // We need to return a value
    return Action::UNKNOWN;
}

inline String stringFromAction(const Action inAction)
{
    switch (inAction)
    {
    case Action::DIRECTION:
        return "DIRECTION";
    case Action::GET_ALTITUDE:
        return "GET_ALTITUDE";
    case Action::GET_BATTERY_PERCENTAGE:
        return "GET_BATTERY_PERCENTAGE";
    case Action::GET_DEVICE_NAME:
        return "GET_DEVICE_NAME";
    case Action::GET_VERSION:
        return "GET_VERSION";
    case Action::RUN_SOUND:
        return "RUN_SOUND";
    case Action::SET_ALTITUDE:
        return "SET_ALTITUDE";
    case Action::SET_DEVICE_NAME:
        return "SET_DEVICE_NAME";
    case Action::SET_VERSION:
        return "SET_VERSION";
    case Action::STOP_SOUND:
        return "STOP_SOUND";
    case Action::END:
        return "END";
    case Action::UNKNOWN:
        return "UNKNOWN";
    default:
        return "Not an defined action.";
    }
}


inline Type typeFromString(const String& inType)
{
    if (inType == "CMD")
        return Type::COMMAND;
    else if (inType == "QRY")
    {
        return Type::QUERY;
    }
    else
        // We need to return a value
        return Type::UNKNOWN;
}
}
}