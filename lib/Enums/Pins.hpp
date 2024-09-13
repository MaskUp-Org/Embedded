/*
 * Created on Tue Sep 12 2024
 *
 * Copyright (c) 2024 MaskUp
 */


#pragma once

namespace MaskUP
{
namespace Enum
{
enum class Pin : int
{
    UNKNOWN = 1000,

    POWERBUTTON = 0,
    EMERGENCYBUTTON = 2,
    RIGHTVIBRATOR = 16,
    LEFTVIBRATOR = 17,
    SERVOMOTOR = 32,
    BATTERY = 35,

    END = 1001
};

inline int fromPinToInt(const Pin inPin)
{
    return static_cast<int> (inPin);
}

}
}