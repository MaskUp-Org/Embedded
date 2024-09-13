#pragma once
#include "Enums.h"

#include <Arduino.h>

namespace MaskUP
{
namespace Communication
{

class IResponse
{
public:
    virtual ~IResponse() = default;

    virtual void processNotOkResponse(Enum::ReturnValue inReturnValue) = 0;
    virtual void processRequestResponse(::MaskUP::Enum::ReturnValue inReturnValue) = 0;
    virtual void processRequestResponse(::MaskUP::Enum::ReturnValue inReturnValue, ::MaskUP::Enum::Request inRequest, String value) = 0;
    virtual void processRequestResponse(::MaskUP::Enum::ReturnValue inReturnValue, ::MaskUP::Enum::Request inRequest, uint32_t value) = 0;
};

}
}
