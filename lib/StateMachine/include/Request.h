/*
 * Created on Wed Aug 28 2024
 *
 * Copyright (c) 2024 MaskUp
 */

#pragma once

#include <memory>
#include <string>
#include "Enums.h"

namespace MaskUP
{
namespace StateMachine
{
class Request
{
public:

    ::MaskUP::Enum::Component m_Component;
    ::MaskUP::Enum::Request m_request;

    std::string m_str;
    uint32_t m_i;
    ::MaskUP::Enum::Position m_pos;

    ::MaskUP::Enum::Args m_argType;
};

}
}