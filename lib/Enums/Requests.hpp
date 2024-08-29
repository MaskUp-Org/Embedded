/*
 * Created on Tue Aug 27 2024
 *
 * Copyright (c) 2024 MaskUp
 */

#pragma once

namespace MaskUP
{
namespace Enum
{

enum class Requests 
{
    UNKNOWN,

    CHANGE_POSITION,
    CHANGE_DEVICE_NAME,
    CHANGE_DEVICE_VERSION,
    RUN_VIBRATOR,
    EMERGENCY_BUTTON,
    PLAY_SOUND,
    STOP_SOUND,
    GET_BATTERY_PERCENTAGE,
    GET_POSITION,
    GET_DEVICE_NAME,

    END
};
}
}
