/*
 * Created on Sat Aug 31 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUP
 */

#pragma once

#include "Enums.h"
#include "StateMachine.h"



namespace MaskUP
{
namespace Communication
{

class ICommunication
{
public:

    void registerStateMachine(std::shared_ptr<::MaskUP::StateMachine::StateMachine> inpStateMachine);
    void request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest);
    void request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const uint32_t inArg);
    void request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Side inArg);
    void request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Position inArg);
    void request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const std::string& inArg);

private:
    std::shared_ptr<::MaskUP::StateMachine::StateMachine> m_pStateMachine;
};
}
}