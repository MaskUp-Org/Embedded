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


    END
};

inline Action actionFromString(const String& inAction)
{
    if (inAction == "set_altitude")
        return Action::SET_ALTITUDE;

    else if (inAction == "direction")
        return Action::DIRECTION;
    else if (inAction == "get_battery")
        return Action::GET_BATTERY_PERCENTAGE;
    else if (inAction == "get_altitude")
        return Action::GET_ALTITUDE;
    else if (inAction == "set_version")
        return Action::SET_VERSION;
    else if (inAction == "stop_sound")
        return Action::STOP_SOUND;
    else if (inAction == "run_sound")
        return Action::RUN_SOUND;
    else if (inAction == "set_device_name")
        return Action::SET_DEVICE_NAME;
    else if (inAction == "get_device_name")
        return Action::GET_DEVICE_NAME;
    else if (inAction == "get_version")
        return Action::GET_VERSION;

    else
        // We need to return a value
        return Action::UNKNOWN;
}

inline Type typeFromString(const String& inType)
{
    if (inType == "command")
        return Type::COMMAND;
    else if (inType == "query")
        return Type::QUERY;
    else
        // We need to return a value
        return Type::UNKNOWN;
}
}
}