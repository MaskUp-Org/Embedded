/*
 * Created on Sat Aug 17 2024
 *
 * Copyright (c) 2024 MaskUp
 */


#pragma once

#include <Arduino.h>
#include <string>

namespace MaskUP
{
namespace Enum
{
enum class ReturnValue
{
    UNKNOWN,

    OK,
    ERROR_OCCURED,
    COMPONENT_NOT_FOUND,
    COMPONENT_NOT_ALLOWED,
    INVALID_POINTER,
    EMPTY_QUEUE,
    EMPTY_REQUEST,

    END
};
inline String fromReturnValueToString(const ReturnValue inValue)
{
    String ret;
    switch (inValue)
    {
    case ReturnValue::OK:
        ret = "OK";
        break;
    case ReturnValue::ERROR_OCCURED:
        ret = "ERROR_OCCURED";
        break;
    case ReturnValue::COMPONENT_NOT_FOUND:
        ret = "COMPONENT_NOT_FOUND";
        break;
    case ReturnValue::COMPONENT_NOT_ALLOWED:
        ret = "COMPONENT_NOT_ALLOWED";
        break;
    case ReturnValue::INVALID_POINTER:
        ret = "INVALID_POINTER";
        break;
    case ReturnValue::EMPTY_QUEUE:
        ret = "EMPTY_QUEUE";
        break;
    case ReturnValue::EMPTY_REQUEST:
        ret = "EMPTY_REQUEST";
        break;
    case ReturnValue::UNKNOWN:
        ret = "UNKNOWN";
        break;
    case ReturnValue::END:
        ret = "END";
        break;

    default:
        ret = "UNKNOWN";
        break;
    }
    return ret;
}




}
}