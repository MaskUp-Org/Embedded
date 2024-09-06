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

enum class Request
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
    GET_DEVICE_VERSION,
    RP_FIRST_EXIT,
    RP_SECOND_EXIT,
    RP_THIRD_EXIT,
    RP_FOURTH_EXIT,

    END
};

inline uint16_t fromRoundAboutToIt(const Request inReq)
{
    uint16_t ret = 0;
    switch (inReq)
    {
    case Request::RP_FIRST_EXIT:
        ret = 1;
        break;
    case Request::RP_SECOND_EXIT:
        ret = 2;
        break;
    case Request::RP_THIRD_EXIT:
        ret = 3;
        break;
    case Request::RP_FOURTH_EXIT:
        ret = 4;
        break;
    default:
        break;
    }
    return ret;
}

}
}
