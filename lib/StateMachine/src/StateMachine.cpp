/*
 * Created on Sat Aug 17 2024
 *
 * Copyright (c) 2024 MaskUp
 */

#include "StateMachine.h"
#include "FileReader.h"
#include <mutex>

namespace MaskUP
{
namespace StateMachine
{

StateMachine::StateMachine() :
    m_pLeftBCHeadPhone(nullptr),
    m_pRightBCHeadPhone(nullptr),
    m_pLeftVibrator(nullptr),
    m_pRightVibrator(nullptr),
    m_pServomotor(nullptr),
    m_pEsp32(nullptr),
    m_pBattery(nullptr),
    m_standardRequest(),
    m_emergencyRequest(),
    m_state(),
    m_pResponseManager(nullptr),
    m_allowedComponentsToRequest(),
    m_requiredComponentsToStart(),
    m_mtx()
{

}

void StateMachine::lock()
{
    m_mtx.lock();
}

void StateMachine::unlock()
{
    m_mtx.unlock();
}

void StateMachine::setupQueues()
{
    Serial.println("Enter function : StateMachine::setupQueues");
    m_emergencyRequest = std::vector<Request>();
    m_standardRequest = std::vector<Request>();
    m_emergencyRequest.reserve(50);
    m_standardRequest.reserve(50);

    Serial.println("left function : StateMachine::setupQueues");
}

void StateMachine::clearQueue()
{
    if (m_state != ::MaskUP::Enum::State::WORKING
        && !m_emergencyRequest.empty()
        || m_state != ::MaskUP::Enum::State::WORKING
        && !m_standardRequest.empty()
        )
    {
        Serial.println("Enter function : StateMachine::clearQueue");
        m_mtx.lock();
        // We save the actual state, we will return to it after working
        auto state = m_state;
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
                if (m_emergencyRequest.begin()->m_request != ::MaskUP::Enum::Request::GET_BATTERY_PERCENTAGE
                    && m_emergencyRequest.begin()->m_request != ::MaskUP::Enum::Request::GET_DEVICE_NAME
                    && m_emergencyRequest.begin()->m_request != ::MaskUP::Enum::Request::GET_DEVICE_VERSION
                    && m_emergencyRequest.begin()->m_request != ::MaskUP::Enum::Request::GET_POSITION
                    )
                {
                    m_pResponseManager->processRequestResponse(val);
                }
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
                m_pResponseManager->processNotOkResponse(val);
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
                // Now we notify the smartphone
                m_pResponseManager->processNotOkResponse(val);
                break;
            }
        }
        changeState(state);
        m_mtx.unlock();
        Serial.println("left function : StateMachine::clearQueue");
    }
}

void StateMachine::checkBattery()
{
    Serial.println("Enter function : StateMachine::checkBattery");
    if (m_pBattery->getBatteryPercentage() < 20 && m_pServomotor->getPosition() != ::MaskUP::Enum::Position::M1000)
    {
        m_pServomotor->changePosition(::MaskUP::Enum::Position::M1000);
        Serial.println("Switched to first position, Battery low.");
    }
    Serial.println("left function : StateMachine::checkBattery");
}

void StateMachine::changeState(const ::MaskUP::Enum::State inState)
{
    Serial.println("Enter function : StateMachine::changeState");
    if (inState == ::MaskUP::Enum::State::UNKNOWN || inState == ::MaskUP::Enum::State::END)
    {
        return;
    }

    m_pEsp32->m_state = inState;
    m_pLeftVibrator->m_state = inState;
    m_pServomotor->m_state = inState;
    m_pRightVibrator->m_state = inState;

    Serial.println("left function : StateMachine::changeState");
}

bool StateMachine::isAllowed(const ::MaskUP::Enum::Component inComponent)
{
    Serial.println("Enter function : StateMachine::isAllowed");
    bool ret = false;

    for (const auto& allowed : m_allowedComponentsToRequest)
    {
        if (inComponent == allowed)
        {
            ret = true;
        }
    }
    Serial.println("left function : StateMachine::isAllowed");
    return ret;
}

::MaskUP::Enum::ReturnValue StateMachine::act(const::MaskUP::StateMachine::Request& inRequest)
{
    Serial.println("Enter function : StateMachine::act");
    ::MaskUP::Enum::ReturnValue res = ::MaskUP::Enum::ReturnValue::END;

    switch (inRequest.m_Component)
    {
    case ::MaskUP::Enum::Component::ESP_32:
        Serial.println("Request = " + ::MaskUP::Enum::fromRequestToString(inRequest.m_request));
        res = esp32Actions(inRequest.m_request, inRequest.m_str);
        break;
    case ::MaskUP::Enum::Component::LEFTVIBRATOR:
        res = lVibratorActions();
        break;
    case ::MaskUP::Enum::Component::RIGHTVIBRATOR:
        res = rVibratorActions();
        break;
    case ::MaskUP::Enum::Component::SERVOMOTOR:
        res = servoMotorActions(inRequest.m_pos);
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
    Serial.println("left function : StateMachine::act");
    return res;
}

::MaskUP::Enum::ReturnValue StateMachine::esp32Actions(const ::MaskUP::Enum::Request inRequest, const String& inString)
{
    Serial.println("Enter function : StateMachine::esp32Actions");
    ::MaskUP::Enum::ReturnValue ret = ::MaskUP::Enum::ReturnValue::END;
    if (m_pEsp32 != nullptr
        && m_pEsp32->m_state != ::MaskUP::Enum::State::ERROR
        && m_pEsp32->componentIsReady()
        )
    {
        Serial.println("Request : " + ::MaskUP::Enum::fromRequestToString(inRequest));
        switch (inRequest)
        {
        case ::MaskUP::Enum::Request::CHANGE_DEVICE_NAME:
            Serial.println("Case : Change Device Name");
            m_pEsp32->setDeviceName(inString);
            m_pResponseManager->processRequestResponse(::MaskUP::Enum::ReturnValue::OK);
            ret = ::MaskUP::Enum::ReturnValue::OK;
            break;
        case ::MaskUP::Enum::Request::CHANGE_DEVICE_VERSION:
            Serial.println("Case : Change Device Version");
            m_pEsp32->setDeviceVersion(inString);
            ret = ::MaskUP::Enum::ReturnValue::OK;
            break;
        case ::MaskUP::Enum::Request::GET_DEVICE_NAME:
            Serial.println("Case : Get Device Name");
            m_pResponseManager->processRequestResponse(::MaskUP::Enum::ReturnValue::OK, ::MaskUP::Enum::Request::GET_DEVICE_NAME, m_pEsp32->getDeviceName());
            ret = ::MaskUP::Enum::ReturnValue::OK;
            break;
        case ::MaskUP::Enum::Request::GET_DEVICE_VERSION:
            Serial.println("Case : Get Device Version");
            m_pResponseManager->processRequestResponse(::MaskUP::Enum::ReturnValue::OK, ::MaskUP::Enum::Request::GET_DEVICE_VERSION, m_pEsp32->getDeviceVersion());
            ret = ::MaskUP::Enum::ReturnValue::OK;
            break;
        default:
            break;
        }
    }
    Serial.println("left function : StateMachine::esp32Actions");
    return ret;
}

::MaskUP::Enum::ReturnValue StateMachine::batteryActions()
{
    Serial.println("Enter function : StateMachine::batteryActions");
    ::MaskUP::Enum::ReturnValue ret = ::MaskUP::Enum::ReturnValue::END;
    if (m_pBattery != nullptr
        && m_pBattery->m_state != ::MaskUP::Enum::State::ERROR
        && m_pBattery->m_state != ::MaskUP::Enum::State::WORKING
        && m_pBattery->componentIsReady()
        )
    {

        ret = ::MaskUP::Enum::ReturnValue::OK;
    }
    Serial.println("left function : StateMachine::batteryActions");
    return ret;
}


::MaskUP::Enum::ReturnValue StateMachine::lVibratorActions()
{
    Serial.println("Enter function : StateMachine::lVibratorActions");
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
    Serial.println("left function : StateMachine::lVibratorActions");
    return ret;
}

::MaskUP::Enum::ReturnValue StateMachine::rVibratorActions()
{
    Serial.println("Enter function : StateMachine::rVibratorActions");
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
    Serial.println("Left function : StateMachine::rVibratorActions");
    return ret;
}

::MaskUP::Enum::ReturnValue StateMachine::allVibratorsActions(const ::MaskUP::Enum::Request inRequest)
{
    Serial.println("Enter function : StateMachine::allVibratorsActions");
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
            m_pRightVibrator->stop();
            m_pLeftVibrator->stop();
        }
        ret = ::MaskUP::Enum::ReturnValue::OK;
    }

    Serial.println("Left function : StateMachine::allVibratorsActions");
    return ret;
}

::MaskUP::Enum::ReturnValue StateMachine::servoMotorActions(const ::MaskUP::Enum::Position inPosition)
{
    Serial.println("Enter function : StateMachine::servoMotorActions");
    ::MaskUP::Enum::ReturnValue ret = ::MaskUP::Enum::ReturnValue::END;
    if (m_pServomotor != nullptr
        && m_pServomotor->componentIsReady()
        )
    {
        m_pServomotor->changePosition(inPosition);
        delay(2000);

        ret = ::MaskUP::Enum::ReturnValue::OK;
    }
    Serial.println("Left function : StateMachine::servoMotorActions");
    return ret;
}

void StateMachine::setRequiredComponentsToStart()
{
    Serial.println("Enter function : StateMachine::setRequiredComponentsToStart");
    String components = ::MaskUP::Tools::getDeviceInformation("/AllowedComponents");
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
    Serial.println("Left function : StateMachine::setRequiredComponentsToStart");
}

void StateMachine::setAllowedComponentsToRequest()
{
    Serial.println("Enter function : StateMachine::setAllowedComponentsToRequest");
    String components = ::MaskUP::Tools::getDeviceInformation("/RequestComponents");
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
    Serial.println("Left function : StateMachine::setAllowedComponentsToRequest");
}

void StateMachine::registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Position inArg, const ::MaskUP::Enum::Caller inCaller)
{
    Serial.println("Enter function : StateMachine::registerRequest");
    Request req;
    req.m_Component = inComponent;
    req.m_request = inRequest;
    int iValue = static_cast<int> (inArg);
    Serial.println("Position Value = " + iValue);
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
    Serial.println("Left function : StateMachine::registerRequest");
}

void StateMachine::registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Side inArg)
{
    Serial.println("Enter function : StateMachine::registerRequest");
    Request req;
    req.m_Component = inComponent;
    req.m_request = inRequest;
    req.m_side = inArg;
    req.m_argType = ::MaskUP::Enum::Args::SIDE;
    m_standardRequest.push_back(req);
    Serial.println("Left function : StateMachine::registerRequest");
}

void StateMachine::registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const uint32_t inArg)
{
    Serial.println("Enter function : StateMachine::registerRequest");
    Request req;
    req.m_Component = inComponent;
    req.m_request = inRequest;
    req.m_i = inArg;
    req.m_argType = ::MaskUP::Enum::Args::SIDE;
    m_standardRequest.push_back(req);
    Serial.println("Left function : StateMachine::registerRequest");
}

void StateMachine::registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const String& inArg)
{
    Serial.println("Enter function : StateMachine::registerRequest");
    Request req;
    req.m_Component = inComponent;
    req.m_request = inRequest;
    req.m_str = inArg;
    req.m_argType = ::MaskUP::Enum::Args::STR;
    m_standardRequest.push_back(req);
    Serial.println("Left function : StateMachine::registerRequest");
}

Request StateMachine::emptyRequest()
{
    Serial.println("Enter function : StateMachine::emptyRequest");
    Request req;
    req.m_Component = ::MaskUP::Enum::Component::UNKNOWN;
    req.m_request = ::MaskUP::Enum::Request::UNKNOWN;
    req.m_argType = ::MaskUP::Enum::Args::NONE;
    req.m_i = 0;
    req.m_pos = ::MaskUP::Enum::Position::UNKNOWN;
    req.m_side = ::MaskUP::Enum::Side::UNKNOWN;
    req.m_str = "";
    Serial.println("Left function : StateMachine::emptyRequest");
    return req;
}

void StateMachine::registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest)
{
    Serial.println("Enter function : StateMachine::registerRequest");
    auto req = Request();
    req.m_Component = inComponent;
    req.m_request = inRequest;
    m_standardRequest.push_back(req);
    Serial.println("component = " + ::MaskUP::Enum::fromComponentToString(inComponent) + " - request = " + ::MaskUP::Enum::fromRequestToString(inRequest));
    Serial.println("Left function : StateMachine::registerRequest");
}

void StateMachine::addResponseManager(std::shared_ptr<::MaskUP::Communication::IResponse> inResponseManager)
{
    Serial.println("Enter function : StateMachine::addResponseManager");
    m_pResponseManager = inResponseManager;
    Serial.println("Left function : StateMachine::addResponseManager");
}


}
}