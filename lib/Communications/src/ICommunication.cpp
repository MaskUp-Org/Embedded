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
    Serial.println("Enter function :: ICommunication::registerStateMachine");
    try
    {
        m_pStateMachine = inpStateMachine;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    Serial.println("Left function :: ICommunication::registerStateMachine");
}

// For now, we use a state machine made by MaskUp, we only have to change all request methods to change our API
void ICommunication::request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const uint32_t inArg)
{
    Serial.println("Enter function :: ICommunication::request");
    m_pStateMachine->lock();
    m_pStateMachine->registerRequest(inComponent, inRequest, inArg);
    m_pStateMachine->unlock();
    Serial.println("Left function :: ICommunication::request");
}

void ICommunication::request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Side inArg)
{
    Serial.println("Enter function :: ICommunication::request");
    m_pStateMachine->lock();
    m_pStateMachine->registerRequest(inComponent, inRequest, inArg);
    m_pStateMachine->unlock();
    Serial.println("Left function :: ICommunication::request");
}

void ICommunication::request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Position inArg, const ::MaskUP::Enum::Caller inCaller)
{
    Serial.println("Enter function :: ICommunication::request");
    m_pStateMachine->lock();
    m_pStateMachine->registerRequest(inComponent, inRequest, inArg, inCaller);
    m_pStateMachine->unlock();
    Serial.println("Left function :: ICommunication::request");
}

void ICommunication::request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const String& inArg)
{
    Serial.println("Enter function :: ICommunication::request");
    m_pStateMachine->lock();
    m_pStateMachine->registerRequest(inComponent, inRequest, inArg);
    m_pStateMachine->unlock();
    Serial.println("Left function :: ICommunication::request");
}

void ICommunication::request(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest)
{
    Serial.println("Enter function :: ICommunication::request");
    m_pStateMachine->lock();
    m_pStateMachine->registerRequest(inComponent, inRequest);
    m_pStateMachine->unlock();
    Serial.println("Left function :: ICommunication::request");
}

void ICommunication::setStateMachine(std::shared_ptr<::MaskUP::StateMachine::StateMachine> inpStateMachine)
{
    Serial.println("Enter function :: ICommunication::setStateMachine");
    m_pStateMachine->lock();
    m_pStateMachine = inpStateMachine;
    m_pStateMachine->unlock();
    Serial.println("Left function :: ICommunication::setStateMachine");
}

}
}
