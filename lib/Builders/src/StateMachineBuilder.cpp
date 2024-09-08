/*
 * Created on Sat Aug 17 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUp
 */

#include "StateMachineBuilder.h"


namespace MaskUP
{
namespace Build
{

StateMachineBuilder* StateMachineBuilder::reset()
{
    m_pStateMachine = ::MaskUP::Tools::make_unique <::MaskUP::StateMachine::StateMachine>();
    m_isReset = true;
    return this;
}

StateMachineBuilder* StateMachineBuilder::buildESP32()
{
    String deviceName = ::MaskUP::Tools::getDeviceInformation("DeviceName");
    String deviceVersion = ::MaskUP::Tools::getDeviceInformation("DeviceVersion");
    m_pStateMachine->m_pEsp32 = ESP_32Builder()
                                .reset()
                                ->buildDeviceName(deviceName)
                                ->buildDeviceVersion(deviceVersion)
                                ->build();
    return this;
}

StateMachineBuilder* StateMachineBuilder::setMandatoryComponents()
{
    String components = ::MaskUP::Tools::getDeviceInformation("MandatoryComponents");
    char* tmp = strtok(strdup(components.c_str()), ";");
    do
    {
        String str(tmp);
        ::MaskUP::Enum::Component tmpComponent = ::MaskUP::Enum::fromStringToComponent(str);
        if (tmpComponent != ::MaskUP::Enum::Component::UNKNOWN
                || tmpComponent != ::MaskUP::Enum::Component::ALLVIBRATORS
           )
        {
            m_mandatoriesComponents.push_back((tmpComponent));
        }
    } while (tmp = strtok(nullptr, ";"));
    return this;
}

StateMachineBuilder* StateMachineBuilder::buildLeftVibrator()
{
    m_pStateMachine->m_pLeftVibrator = VibratorBuilder()
                                       .reset()
                                       ->assignSide(::MaskUP::Enum::Side::LEFT)
                                       ->build();
    return this;
}

StateMachineBuilder* StateMachineBuilder::buildRightVibrator()
{
    m_pStateMachine->m_pRightVibrator = VibratorBuilder()
                                        .reset()
                                        ->assignSide(::MaskUP::Enum::Side::RIGHT)
                                        ->build();
    return this;
}

StateMachineBuilder* StateMachineBuilder::buildLeftBCHeadPhone()
{
    m_pStateMachine->m_pLeftBCHeadPhone = BCHeadphoneBuilder()
                                          .reset()
                                          ->assignSide(::MaskUP::Enum::Side::LEFT)
                                          ->build();
    return this;
}

StateMachineBuilder* StateMachineBuilder::buildRightBCHeadPhone()
{
    m_pStateMachine->m_pRightBCHeadPhone = BCHeadphoneBuilder()
                                           .reset()
                                           ->assignSide(::MaskUP::Enum::Side::RIGHT)
                                           ->build();
    return this;
}

StateMachineBuilder* StateMachineBuilder::buildServomotor()
{
    m_pStateMachine->m_pServomotor = ServoMotorBuilder()
                                     .reset()
                                     ->assignDefaultPosition(::MaskUP::Enum::Position::M1000)
                                     ->build();
    return this;
}

StateMachineBuilder* StateMachineBuilder::setAllowedComponentsToRequest()
{
    m_pStateMachine->setAllowedComponentsToRequest();
    return this;
}

StateMachineBuilder* StateMachineBuilder::setRequiredComponentsToStart()
{
    m_pStateMachine->setRequiredComponentsToStart();
    return this;
}



std::unique_ptr<::MaskUP::StateMachine::StateMachine> StateMachineBuilder::build()
{
    if (m_isReset == true)
    {
        m_isReset = false;
        return std::move(m_pStateMachine);
    }
    else
    {
        std::cout << "StateMachineBuilder error : Cannot build StateMachine.\n";
        return nullptr;
    }
}

StateMachineBuilder* StateMachineBuilder::addCallbackFunctions()
{
    return this;
}

}
}
