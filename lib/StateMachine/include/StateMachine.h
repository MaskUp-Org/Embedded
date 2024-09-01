/*
 * Created on Sat Aug 17 2024
 *
 * Copyright (c) 2024 MaskUp
 */

#pragma once

#include <memory>
#include <vector>

#include "BCHeadphone.h"
#include "ESP_32.h"
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
    void changeState(const ::MaskUP::Enum::State inState);
    void registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Position inArg);
    void registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const ::MaskUP::Enum::Side inArg);
    void registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const uint32_t inArg);
    void registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest, const std::string& inArg);
    void registerRequest(const ::MaskUP::Enum::Component inComponent, const ::MaskUP::Enum::Request inRequest);

private:
    /**
     * Verify if the component is allowed to ask for a state changement
     */
    bool isAllowed(const ::MaskUP::Enum::Component inComponent);

    ::MaskUP::Enum::ReturnValue act(const ::MaskUP::StateMachine::Request& inRequest);
    ::MaskUP::Enum::ReturnValue errorOccured(const ::MaskUP::StateMachine::Request& inRequest, const ::MaskUP::Enum::ReturnValue);

    /**
     * Clear all queues, prioritize the emergency queue
     */
    void clearQueue();

    std::unique_ptr<::MaskUP::Component::BCHeadphone> m_pLeftBCHeadPhone;
    std::unique_ptr<::MaskUP::Component::BCHeadphone> m_pRightBCHeadPhone;
    std::unique_ptr<::MaskUP::Component::Vibrator> m_pLeftVibrator;
    std::unique_ptr<::MaskUP::Component::Vibrator> m_pRightVibrator;
    std::unique_ptr<::MaskUP::Component::ServoMotor> m_pServomotor;
    std::unique_ptr<::MaskUP::Component::ESP_32> m_pEsp32;

    std::vector<::MaskUP::StateMachine::Request> m_standardRequest;
    std::vector<::MaskUP::StateMachine::Request> m_emergencyRequest;

    std::shared_ptr<::MaskUP::Enum::State> m_pState;

    std::vector<::MaskUP::Enum::Component> m_allowedComponentsToRequest;
    std::vector<::MaskUP::Enum::Component> m_requiredComponentsToStart;

};

}
}