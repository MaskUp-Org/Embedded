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
    COMPONENT_NOT_FOUND,
    COMPONENT_NOT_ALLOWED,
    ERROR_OCCURED,
    EMPTY_QUEUE,
    EMPTY_REQUEST,

    END
};

}
}