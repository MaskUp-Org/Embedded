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
    RESET,

    END
};

inline Request fromStringToRequest(const String inStr)
{
    {
        std::string tmp = strdup(inStr.c_str());

        std::transform(tmp.begin(), tmp.end(), tmp.begin(), std::ptr_fun<int, int>(std::toupper));

        if (tmp == "CHANGE_POSITION")
        {
            return ::MaskUP::Enum::Request::CHANGE_POSITION;
        }
        else if (tmp == "CHANGE_DEVICE_NAME")
        {
            return ::MaskUP::Enum::Request::CHANGE_DEVICE_NAME;
        }
        else if (tmp == "CHANGE_DEVICE_VERSION")
        {
            return ::MaskUP::Enum::Request::CHANGE_DEVICE_VERSION;
        }
        else if (tmp == "RUN_VIBRATOR")
        {
            return ::MaskUP::Enum::Request::RUN_VIBRATOR;
        }
        else if (tmp == "EMERGENCY_BUTTON")
        {
            return ::MaskUP::Enum::Request::EMERGENCY_BUTTON;
        }
        else if (tmp == "PLAY_SOUND")
        {
            return ::MaskUP::Enum::Request::PLAY_SOUND;
        }
        else if (tmp == "STOP_SOUND")
        {
            return ::MaskUP::Enum::Request::STOP_SOUND;
        }
        else if (tmp == "GET_BATTERY_PERCENTAGE")
        {
            return ::MaskUP::Enum::Request::GET_BATTERY_PERCENTAGE;
        }
        else if (tmp == "GET_POSITION")
        {
            return ::MaskUP::Enum::Request::GET_POSITION;
        }
        else if (tmp == "GET_DEVICE_NAME")
        {
            return ::MaskUP::Enum::Request::GET_DEVICE_NAME;
        }
        else if (tmp == "GET_DEVICE_VERSION")
        {
            return ::MaskUP::Enum::Request::GET_DEVICE_VERSION;
        }
        else if (tmp == "RP_FIRST_EXIT")
        {
            return ::MaskUP::Enum::Request::RP_FIRST_EXIT;
        }
        else if (tmp == "RP_SECOND_EXIT")
        {
            return ::MaskUP::Enum::Request::RP_SECOND_EXIT;
        }
        else if (tmp == "RP_THIRD_EXIT")
        {
            return ::MaskUP::Enum::Request::RP_THIRD_EXIT;
        }
        else if (tmp == "RP_FOURTH_EXIT")
        {
            return ::MaskUP::Enum::Request::RP_FOURTH_EXIT;
        }
        return ::MaskUP::Enum::Request::UNKNOWN;
    }
}

inline String fromRequestToString(const Request inRequest)
{
    switch (inRequest)
    {
    case Request::UNKNOWN:
        return "UNKNOWN";
    case Request::CHANGE_POSITION:
        return "CHANGE_POSITION";
    case Request::CHANGE_DEVICE_VERSION:
        return "CHANGE_DEVICE_VERSION";
    case Request::RUN_VIBRATOR:
        return "RUN_VIBRATOR";
    case Request::EMERGENCY_BUTTON:
        return "EMERGENCY_BUTTON";
    case Request::PLAY_SOUND:
        return "PLAY_SOUND";
    case Request::STOP_SOUND:
        return "STOP_SOUND";
    case Request::GET_BATTERY_PERCENTAGE:
        return "GET_BATTERY_PERCENTAGE";
    case Request::GET_POSITION:
        return "GET_POSITION";
    case Request::GET_DEVICE_NAME:
        return "GET_DEVICE_NAME";
    case Request::GET_DEVICE_VERSION:
        return "GET_DEVICE_VERSION";
    case Request::RP_FIRST_EXIT:
        return "RP_FIRST_EXIT";
    case Request::RP_SECOND_EXIT:
        return "RP_SECOND_EXIT";
    case Request::RP_THIRD_EXIT:
        return "RP_THIRD_EXIT";
    case Request::RP_FOURTH_EXIT:
        return "RP_FOURTH_EXIT";
    case Request::END:
    default:
        return "END";
    }
}

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
