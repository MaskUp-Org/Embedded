/*
 * Created on Wed Aug 28 2024
 *
 * Copyright (c) 2024 MaskUp
 */

#pragma once
#include <Arduino.h>

#include <memory>
#include "Enums.h"

namespace MaskUP
{
namespace StateMachine
{
class Request
{
public:
    Request() :
        m_Component(::MaskUP::Enum::Component::UNKNOWN),
        m_request(::MaskUP::Enum::Request::UNKNOWN),
        m_str(""),
        m_i(0),
        m_pos(::MaskUP::Enum::Position::UNKNOWN),
        m_argType(::MaskUP::Enum::Args::UNKNOWN)
    {

    }


    ::MaskUP::Enum::Component m_Component;
    ::MaskUP::Enum::Request m_request;

    String m_str;
    uint32_t m_i;
    ::MaskUP::Enum::Position m_pos;
    ::MaskUP::Enum::Side m_side;

    ::MaskUP::Enum::Args m_argType;
};

}
}