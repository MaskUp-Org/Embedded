/*
 * Created on Sat Aug 17 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUp
 */

#pragma once

#include "StateMachine.h"
#include "IBuilder.h"
#include "needed.hpp"
#include "JsonReader.h"
#include "Component.hpp"

#include <vector>
#include <memory>

namespace MaskUP
{
namespace Build
{
class StateMachineBuilder : public IBuilder<::MaskUP::StateMachine::StateMachine>
{
public:
    virtual StateMachineBuilder* reset() override;

    ::MaskUP::StateMachine::StateMachine* assignESP32();
    ::MaskUP::StateMachine::StateMachine* setMandatoryComponents();
    ::MaskUP::StateMachine::StateMachine* assignLeftVibrator();
    ::MaskUP::StateMachine::StateMachine* assignRightVibrator();
    ::MaskUP::StateMachine::StateMachine* assignLeftBCHeadPhone();
    ::MaskUP::StateMachine::StateMachine* assignRightBCHeadPhone();
    ::MaskUP::StateMachine::StateMachine* assignServomotor();
    ::MaskUP::StateMachine::StateMachine* assignEmergencyButton();

    virtual std::unique_ptr<::MaskUP::StateMachine::StateMachine> build() override;

private:
    std::unique_ptr<::MaskUP::StateMachine::StateMachine> m_pStateMachine;
    std::vector<::MaskUP::Enum::Component> m_mandatoriesComponents;
    ::MaskUP::Tools::JsonReader m_fileReader;
};
}
}