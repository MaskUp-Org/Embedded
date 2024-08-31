/*
 * Created on Sat Aug 31 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUP
 */

#pragma once

#include "Enums.h"
#include "StateMachine.h"

#include <iostream>
#include <memory>
#include <string>

namespace MaskUP
{
namespace Communication
{

class ICommunication
{
public:

    void registerStateMachine(std::shared_ptr<::MaskUP::StateMachine::StateMachine> inpStateMachine)
    {
        try
        {
            m_pStateMachine = inpStateMachine;
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    // For now, we use a state machine made by MaskUp, we only have to change all request methods to change our API

    ::MaskUP::Enum::ReturnValue request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const uint32_t inArg)
    {
        m_pStateMachine->registerRequest(inComponent, inRequest, inArg);
    }
    ::MaskUP::Enum::ReturnValue request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Position inArg)
    {
        m_pStateMachine->registerRequest(inComponent, inRequest, inArg);
    }
    ::MaskUP::Enum::ReturnValue request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const std::string& inArg)
    {
        m_pStateMachine->registerRequest(inComponent, inRequest, inArg);
    }
    ::MaskUP::Enum::ReturnValue request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest)
    {
        m_pStateMachine->registerRequest(inComponent, inRequest);
    }
private:
    std::shared_ptr<::MaskUP::StateMachine::StateMachine> m_pStateMachine;
};
}
}