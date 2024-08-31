/*
 * Created on Sat Aug 17 2024
 *
 * Copyright (c) 2024 MaskUp
 */

#include "StateMachine.h"

namespace MaskUP
{
namespace StateMachine
{

void StateMachine::clearQueue()
{
    // We save the actual state, we will return to it after working
    auto state = m_pState;

    changeState(::MaskUP::Enum::State::WORKING);

    // Only one request by loop iteration, focus on emergencies first
    if (!m_emergencyRequest.empty())
    {
        auto val = act(*m_emergencyRequest.begin());
        switch (val)
        {
        case ::MaskUP::Enum::ReturnValue::OK:
            //Everything worked well, just clear the queue now
            m_emergencyRequest.erase(m_emergencyRequest.begin());
            break;
            // If anything bad happens, we need to return one of those Return values, and manage it correctly
        case ::MaskUP::Enum::ReturnValue::ERROR_OCCURED:
        case ::MaskUP::Enum::ReturnValue::COMPONENT_NOT_ALLOWED:
        case ::MaskUP::Enum::ReturnValue::COMPONENT_NOT_FOUND:
        case ::MaskUP::Enum::ReturnValue::EMPTY_REQUEST:
        case ::MaskUP::Enum::ReturnValue::EMPTY_QUEUE:
        case ::MaskUP::Enum::ReturnValue::END:
        case ::MaskUP::Enum::ReturnValue::UNKNOWN:
        default:
            //Every component has to switch to Error mode
            changeState(::MaskUP::Enum::State::ERROR);
            // Now we can fix the issue
            errorOccured(*m_emergencyRequest.begin(), val);
            break;
        }
    }
    else if (!m_standardRequest.empty())
    {
        auto val = act(*m_standardRequest.begin());

        switch (val)
        {
        case ::MaskUP::Enum::ReturnValue::OK:
            //Everything good, just clear the queue
            m_standardRequest.erase(m_standardRequest.begin());
            break;

        case ::MaskUP::Enum::ReturnValue::ERROR_OCCURED:
        case ::MaskUP::Enum::ReturnValue::COMPONENT_NOT_ALLOWED:
        case ::MaskUP::Enum::ReturnValue::COMPONENT_NOT_FOUND:
        case ::MaskUP::Enum::ReturnValue::EMPTY_REQUEST:
        case ::MaskUP::Enum::ReturnValue::EMPTY_QUEUE:
        case ::MaskUP::Enum::ReturnValue::END:
        case ::MaskUP::Enum::ReturnValue::UNKNOWN:
        default:
            //Every component has to switch to Error mode
            changeState(::MaskUP::Enum::State::ERROR);
            // Now we can fix the issue
            errorOccured(*m_emergencyRequest.begin(), val);
            break;
        }
    }
    changeState(*state);
}

void StateMachine::changeState(const ::MaskUP::Enum::State inState)
{
    if (inState == ::MaskUP::Enum::State::UNKNOWN || inState == ::MaskUP::Enum::State::END)
    {
        return;
    }
    m_pState = std::make_shared<::MaskUP::Enum::State>(inState);
}

bool StateMachine::isAllowed(const ::MaskUP::Enum::Component inComponent)
{
    bool ret = false;

    for (const auto& allowed : m_allowedComponentsToRequest)
    {
        if (inComponent == allowed)
        {
            ret = true;
        }
    }
    return ret;
}

::MaskUP::Enum::ReturnValue StateMachine::act(const::MaskUP::StateMachine::Request& inRequest)
{
    ::MaskUP::Enum::ReturnValue res = ::MaskUP::Enum::ReturnValue::END;
    return res;
}

void registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Position inArg)
{

}

void registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const uint32_t inArg)
{

}

void registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const std::string& inArg)
{

}

void registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest)
{

}

}
}