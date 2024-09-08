/*
 * Created on Sat Aug 31 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUP
 */

#include "ICommunication.h"
#include <iostream>
#include <memory>

namespace MaskUP
{
namespace Communication
{

ICommunication::ICommunication() :
    m_pStateMachine(nullptr)
{

}

void ICommunication::registerStateMachine(std::shared_ptr<::MaskUP::StateMachine::StateMachine> inpStateMachine)
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

void ICommunication::request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const uint32_t inArg)
{
    m_pStateMachine->registerRequest(inComponent, inRequest, inArg);
}

void ICommunication::request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Side inArg)
{
    m_pStateMachine->registerRequest(inComponent, inRequest, inArg);
}

void ICommunication::request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Position inArg, const ::MaskUP::Enum::Caller inCaller)
{
    m_pStateMachine->registerRequest(inComponent, inRequest, inArg, inCaller);
}

void ICommunication::request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const String& inArg)
{
    m_pStateMachine->registerRequest(inComponent, inRequest, inArg);
}

void ICommunication::request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest)
{
    m_pStateMachine->registerRequest(inComponent, inRequest);
}

void ICommunication::setStateMachine (std::shared_ptr<::MaskUP::StateMachine::StateMachine> inpStateMachine)
{
    m_pStateMachine = inpStateMachine;
}

}
}
