/*
 * Created on Sat Aug 17 2024
 *
 * Copyright (c) 2024 MaskUp
 */

#include "StateMachine.h"
#include "FileReader.h"

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
    m_pEsp32->m_state = inState;
    m_pLeftBCHeadPhone->m_state = inState;
    m_pLeftVibrator->m_state = inState;
    m_pServomotor->m_state = inState;
    m_pRightBCHeadPhone->m_state = inState;
    m_pRightVibrator->m_state = inState;
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

    switch (inRequest.m_Component)
    {
    case ::MaskUP::Enum::Component::ESP_32:
        res = esp32Actions(inRequest.m_request, inRequest.m_str);
        break;
    case ::MaskUP::Enum::Component::LEFTVIBRATOR:
        res = lVibratorActions();
        break;
    case ::MaskUP::Enum::Component::RIGHTVIBRATOR:
        res = rVibratorActions();
        break;
    case ::MaskUP::Enum::Component::SERVOMOTOR:
        res = servoMotorActions();
        break;
    case ::MaskUP::Enum::Component::BATTERY:
        res = batteryActions();
        break;
    case ::MaskUP::Enum::Component::ALLVIBRATORS:
        res = allVibratorsActions(inRequest.m_request);
        break;
    case ::MaskUP::Enum::Component::LEFTBCHEADPHONE:
    case ::MaskUP::Enum::Component::RIGHTBCHEADPHONE:
    default:
        break;
    }
    return res;
}

::MaskUP::Enum::ReturnValue StateMachine::esp32Actions(const ::MaskUP::Enum::Request inRequest, const String& inString)
{
    ::MaskUP::Enum::ReturnValue ret = ::MaskUP::Enum::ReturnValue::END;
    if (m_pEsp32 != nullptr
        && m_pEsp32->m_state != ::MaskUP::Enum::State::ERROR
        && m_pEsp32->m_state != ::MaskUP::Enum::State::WORKING
        && m_pEsp32->componentIsReady()
        )
    {
        switch (inRequest)
        {
        case ::MaskUP::Enum::Request::CHANGE_DEVICE_NAME:
            m_pEsp32->setDeviceName(inString);
            ret = ::MaskUP::Enum::ReturnValue::OK;
            break;
        case ::MaskUP::Enum::Request::CHANGE_DEVICE_VERSION:
            m_pEsp32->setDeviceVersion(inString);
            ret = ::MaskUP::Enum::ReturnValue::OK;
            break;
        default:
            break;
        }
    }
    return ret;
}

::MaskUP::Enum::ReturnValue StateMachine::lVibratorActions()
{
    ::MaskUP::Enum::ReturnValue ret = ::MaskUP::Enum::ReturnValue::END;
    if (m_pLeftVibrator != nullptr
        && m_pLeftVibrator->m_state != ::MaskUP::Enum::State::ERROR
        && m_pLeftVibrator->m_state != ::MaskUP::Enum::State::WORKING
        && m_pLeftVibrator->componentIsReady()
        )
    {
        m_pLeftVibrator->run();
        delay(1000);
        m_pLeftVibrator->stop();

        ret = ::MaskUP::Enum::ReturnValue::OK;
    }
    return ret;
}

::MaskUP::Enum::ReturnValue StateMachine::rVibratorActions()
{
    ::MaskUP::Enum::ReturnValue ret = ::MaskUP::Enum::ReturnValue::END;
    if (m_pRightVibrator != nullptr
        && m_pRightVibrator->m_state != ::MaskUP::Enum::State::ERROR
        && m_pRightVibrator->m_state != ::MaskUP::Enum::State::WORKING
        && m_pRightVibrator->componentIsReady()
        )
    {
        m_pRightVibrator->run();
        delay(1000);
        m_pRightVibrator->stop();

        ret = ::MaskUP::Enum::ReturnValue::OK;
    }
    return ret;
}

::MaskUP::Enum::ReturnValue StateMachine::allVibratorsActions(const ::MaskUP::Enum::Request inRequest)
{
    ::MaskUP::Enum::ReturnValue ret = ::MaskUP::Enum::ReturnValue::END;

    // This is ugly, its true, but I dont want to trust the verification and invert the logic
    if (m_pRightVibrator != nullptr
        && m_pRightVibrator->m_state != ::MaskUP::Enum::State::ERROR
        && m_pRightVibrator->m_state != ::MaskUP::Enum::State::WORKING
        && m_pRightVibrator->componentIsReady()
        && m_pLeftVibrator != nullptr
        && m_pLeftVibrator->m_state != ::MaskUP::Enum::State::ERROR
        && m_pLeftVibrator->m_state != ::MaskUP::Enum::State::WORKING
        && m_pLeftVibrator->componentIsReady()
        )
    {
        for (int nbOccurence = 0; nbOccurence < ::MaskUP::Enum::fromRoundAboutToIt(inRequest); nbOccurence += 1)
        {
            m_pRightVibrator->run();
            m_pLeftVibrator->run();
            delay(500);
        }
        ret = ::MaskUP::Enum::ReturnValue::OK;
    }

    return ret;
}

::MaskUP::Enum::ReturnValue StateMachine::servoMotorActions()
{
    ::MaskUP::Enum::ReturnValue ret = ::MaskUP::Enum::ReturnValue::END;
    if (m_pRightVibrator != nullptr
        && m_pRightVibrator->m_state != ::MaskUP::Enum::State::ERROR
        && m_pRightVibrator->m_state != ::MaskUP::Enum::State::WORKING
        && m_pRightVibrator->componentIsReady()
        )
    {
        m_pRightVibrator->run();
        delay(1000);
        m_pRightVibrator->stop();

        ret = ::MaskUP::Enum::ReturnValue::OK;
    }    return ret;
}

void StateMachine::setRequiredComponentsToStart()
{
    String components = ::MaskUP::Tools::getDeviceInformation("AllowedComponents");
    char* tmp = strtok(strdup(components.c_str()), ";");
    do
    {
        String str(tmp);
        ::MaskUP::Enum::Component tmpComponent = ::MaskUP::Enum::fromStringToComponent(str);
        if (tmpComponent != ::MaskUP::Enum::Component::UNKNOWN
            || tmpComponent != ::MaskUP::Enum::Component::ALLVIBRATORS
            )
        {
            m_requiredComponentsToStart.push_back((tmpComponent));
        }
    } while (tmp = strtok(nullptr, ";"));
}

void StateMachine::setAllowedComponentsToRequest()
{
    String components = ::MaskUP::Tools::getDeviceInformation("RequestComponents");
    char* tmp = strtok(strdup(components.c_str()), ";");
    do
    {
        String str(tmp);
        ::MaskUP::Enum::Component tmpComponent = ::MaskUP::Enum::fromStringToComponent(str);
        if (tmpComponent != ::MaskUP::Enum::Component::UNKNOWN
            || tmpComponent != ::MaskUP::Enum::Component::ALLVIBRATORS
            )
        {
            m_allowedComponentsToRequest.push_back((tmpComponent));
        }
    } while (tmp = strtok(nullptr, ";"));
}

void StateMachine::registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Position inArg, const ::MaskUP::Enum::Caller inCaller)
{
    Request req;
    req.m_Component = inComponent;
    req.m_request = inRequest;
    req.m_pos = inArg;
    req.m_argType = ::MaskUP::Enum::Args::POSITION;
    if (inCaller == ::MaskUP::Enum::Caller::BLUETOOTH)
    {
        m_standardRequest.push_back(req);
    }
    else if (inCaller == ::MaskUP::Enum::Caller::EMERGENCYBUTTON)
    {
        m_emergencyRequest.push_back(req);
    }
}

void StateMachine::registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Side inArg)
{
    Request req;
    req.m_Component = inComponent;
    req.m_request = inRequest;
    req.m_side = inArg;
    req.m_argType = ::MaskUP::Enum::Args::SIDE;
    m_standardRequest.push_back(req);
}

void StateMachine::registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const uint32_t inArg)
{
    Request req;
    req.m_Component = inComponent;
    req.m_request = inRequest;
    req.m_i = inArg;
    req.m_argType = ::MaskUP::Enum::Args::SIDE;
    m_standardRequest.push_back(req);
}

void StateMachine::registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const String& inArg)
{
    Request req;
    req.m_Component = inComponent;
    req.m_request = inRequest;
    req.m_str = inArg;
    req.m_argType = ::MaskUP::Enum::Args::STR;
    m_standardRequest.push_back(req);
}

void StateMachine::registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest)
{
    Request req;
    req.m_Component = inComponent;
    req.m_request = inRequest;
    req.m_argType = ::MaskUP::Enum::Args::NONE;
    m_standardRequest.push_back(req);
}

}
}