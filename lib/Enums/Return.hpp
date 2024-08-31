/*
 * Created on Sat Aug 17 2024
 *
 * Copyright (c) 2024 MaskUp
 */


#pragma once

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





}
}