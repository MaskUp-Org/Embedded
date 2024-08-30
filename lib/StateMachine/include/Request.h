/*
 * Created on Wed Aug 28 2024
 *
 * Copyright (c) 2024 MaskUp
 */

#pragma once

#include <memory>
#include <string>
#include "Enums.h"

bool request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const uint32_t inArg);
bool request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Position inArg);
bool request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const std::string& inArg);
bool request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest);

namespace MaskUP
{
namespace StateMachine
{

class Request
{
public:

};

}
}