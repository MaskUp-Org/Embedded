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
#include "FileReader.h"
#include "Enums.h"
#include "IResponse.h"


#include "ESP_32Builder.h"
#include "ServoMotorBuilder.h"
#include "VibratorBuilder.h"
#include "BCHeadPhoneBuilder.h"



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
    //StateMachineBuilder* reset(const std::vector<::MaskUP::Enum::Component>& inMandatories);

    StateMachineBuilder* setMandatoryComponents();
    StateMachineBuilder* buildESP32();
    StateMachineBuilder* buildLeftVibrator();
    StateMachineBuilder* buildRightVibrator();
    StateMachineBuilder* buildLeftBCHeadPhone();
    StateMachineBuilder* buildRightBCHeadPhone();
    StateMachineBuilder* buildServomotor();
    StateMachineBuilder* addCallbackFunctions();
    StateMachineBuilder* setRequiredComponentsToStart();
    StateMachineBuilder* setAllowedComponentsToRequest();
    StateMachineBuilder* setResponseManager(std::shared_ptr <::MaskUP::Communication::IResponse> inResponseManager);


    virtual std::unique_ptr<::MaskUP::StateMachine::StateMachine> build() override;



private:
    std::unique_ptr<::MaskUP::StateMachine::StateMachine> m_pStateMachine;
    std::vector<::MaskUP::Enum::Component> m_mandatoriesComponents;
    bool m_isReset;
};
}
}