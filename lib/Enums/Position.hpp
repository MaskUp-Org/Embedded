/*
 * Created on Sat Aug 17 2024
 *
 * Copyright (c) 2024 Your Company
 */

#pragma once

#include <Arduino.h>
#include <string>

namespace MaskUP
{
namespace Enum
{

enum class Position {
    UNKNOWN,
    M500,
    M1000,
    M2000,
    M3000,
    M5000,
    M6000,

    END
};
inline const String positionToString(Position inPosition)
{
    switch (inPosition)
    {
    case Position::M500:
        return "1000";
    case Position::M1000:
        return "2000";
    case Position::M2000:
        return "3000";
    case Position::M3000:
        return "4000";
    case Position::M5000:
        return "5000";
    case Position::M6000:
        return "6000";
    case Position::END:
        return "Not in range.";
    case Position::UNKNOWN:
    default:
        return "Unknown";
    }
}

inline const int positionToDirection(Position inPosition)
{
    const int first = 245;
    const int last = 110;
    switch (inPosition)
    {
    case Position::M500:
        return first;
    case Position::M1000:
        return first - (first - last) / 5;
    case Position::M2000:
        return first - (first - last) / 5 * 2;
    case Position::M3000:
        return first - (first - last) / 5 * 3;
    case Position::M5000:
        return first - (first - last) / 5 * 4;
    case Position::M6000:
        return last;
    case Position::END:
    case Position::UNKNOWN:
    default:
        return first;
    }
}

inline Position positionFromString(const String& inPosition)
{
    if (inPosition == "500")
        return Position::M500;
    else if (inPosition == "1000")
        return Position::M1000;
    else if (inPosition == "2000")
        return Position::M2000;
    else if (inPosition == "3000")
        return Position::M3000;
    else if (inPosition == "5000")
        return Position::M5000;
    else if (inPosition == "6000")
        return Position::M6000;
    else
        // We need to return a value
        return Position::M500;

}

inline Position positionFromInt(const int inPosition)
{
    if (inPosition == 500)
        return Position::M500;
    else if (inPosition == 1000)
        return Position::M1000;
    else if (inPosition == 2000)
        return Position::M2000;
    else if (inPosition == 3000)
        return Position::M3000;
    else if (inPosition == 5000)
        return Position::M5000;
    else if (inPosition == 6000)
        return Position::M6000;
    else
        // We need to return a default value
        return Position::M500;

}

}
}