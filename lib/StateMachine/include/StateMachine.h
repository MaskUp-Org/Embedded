/*
 * Created on Sat Aug 17 2024
 *
 * Copyright (c) 2024 MaskUp
 */

#pragma once

#include <memory>
#include <vector>
#include <mutex>
#include <Arduino.h>


#include "BCHeadphone.h"
#include "Battery.h"
#include "ESP_32.h"
#include "IResponse.h"
#include "Request.h"
#include "ServoMotor.h"
#include "Vibrator.h"

namespace MaskUP
{
namespace StateMachine
{

class StateMachine
{
public:

    StateMachine();

    void changeState(const ::MaskUP::Enum::State inState);

    void registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Position inArg, const ::MaskUP::Enum::Caller inCaller);
    void registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Side inArg);
    void registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const uint32_t inArg);
    void registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const String& inArg);
    void registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest);

    /**
     * Clear all queues, prioritize the emergency queue
     */
    void clearQueue();

    void setupQueues();

    void checkBattery();

    void lock();

    void unlock();

private:
    /**
     * Verify if the component is allowed to ask for a state changement
     */
    bool isAllowed(const ::MaskUP::Enum::Component inComponent);

    ::MaskUP::Enum::ReturnValue act(const ::MaskUP::StateMachine::Request& inRequest);

    ::MaskUP::Enum::ReturnValue esp32Actions(const ::MaskUP::Enum::Request inRequest, const String& inString);

    ::MaskUP::Enum::ReturnValue lVibratorActions();

    ::MaskUP::Enum::ReturnValue rVibratorActions();

    ::MaskUP::Enum::ReturnValue allVibratorsActions(const ::MaskUP::Enum::Request inRequest);

    ::MaskUP::Enum::ReturnValue servoMotorActions(const ::MaskUP::Enum::Position inPosition);

    ::MaskUP::Enum::ReturnValue batteryActions();

    ::MaskUP::StateMachine::Request emptyRequest();



public:
    std::unique_ptr<::MaskUP::Component::BCHeadphone> m_pLeftBCHeadPhone;
    std::unique_ptr<::MaskUP::Component::BCHeadphone> m_pRightBCHeadPhone;
    std::unique_ptr<::MaskUP::Component::Vibrator> m_pLeftVibrator;
    std::unique_ptr<::MaskUP::Component::Vibrator> m_pRightVibrator;
    std::unique_ptr<::MaskUP::Component::ServoMotor> m_pServomotor;
    std::unique_ptr<::MaskUP::Component::ESP_32> m_pEsp32;
    std::unique_ptr<::MaskUP::Component::Battery> m_pBattery;


private:
    std::vector<::MaskUP::StateMachine::Request> m_standardRequest;
    std::vector<::MaskUP::StateMachine::Request> m_emergencyRequest;

    ::MaskUP::Enum::State m_state;
    std::shared_ptr<::MaskUP::Communication::IResponse>m_pResponseManager;
    std::vector<::MaskUP::Enum::Component> m_allowedComponentsToRequest;
    std::vector<::MaskUP::Enum::Component> m_requiredComponentsToStart;
    std::mutex m_mtx;


public:
    void setRequiredComponentsToStart();
    void setAllowedComponentsToRequest();
    void addResponseManager(std::shared_ptr<::MaskUP::Communication::IResponse> inResponseManager);

};

}
}