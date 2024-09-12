/*
 * Created on Sat Aug 17 2024
 *
 * Copyright (c) 2024 Your Company
 */

#pragma once

namespace MaskUP
{
namespace Enum
{
enum class Side
{
    UNKNOWN,
    LEFT,
    RIGHT,

    END

};

inline String fromSideToString(const Side inSide)
{
    switch (inSide)
    {
    case Side::UNKNOWN:
        return "UNKNOWN";
    case Side::LEFT:
        return "LEFT";
    case Side::RIGHT:
        return "RIGHT";
    case Side::END:
    default:
        return "END";
    }
}
}
}