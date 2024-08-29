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

class StateMachine {
public:

    
    template <typename T>
    void changeState (const T* inpCaller, const ::MaskUP::Enum::State inState);

    template <typename T>
    bool isAllowed (const T *inpCaller);
private:
    void clearQueue ();



    std::unique_ptr <::MaskUP::Component::BCHeadphone> m_pLeftBCHeadPhone;
    std::unique_ptr <::MaskUP::Component::BCHeadphone> m_pRightBCHeadPhone;
    std::unique_ptr <::MaskUP::Component::Vibrator> m_pLeftVibrator;
    std::unique_ptr <::MaskUP::Component::Vibrator> m_pRightVibrator;
    std::unique_ptr <::MaskUP::Component::ServoMotor> m_pServomotor;
    std::unique_ptr <::MaskUP::Component::ESP_32> m_pEsp32;

    std::vector <::MaskUP::StateMachine::Request> m_standardRequest;
    std::vector <::MaskUP::StateMachine::Request> m_emergencyRequest;

    ::MaskUP::Enum::State m_state;

    std::vector <::MaskUP::Enum::Component> m_allowedComponents;
    std::vector <::MaskUP::Enum::Component> m_requiredComponents;
};

}
}