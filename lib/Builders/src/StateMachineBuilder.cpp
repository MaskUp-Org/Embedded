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

StateMachineBuilder* StateMachineBuilder::reset(const std::vector<::MaskUP::Enum::Component>& inMandatories)
{
    m_isReset = true;
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
}

StateMachineBuilder* StateMachineBuilder::buildLeftVibrator()
{
    m_pStateMachine->m_pLeftVibrator = VibratorBuilder()
        .reset()
        ->assignSide(::MaskUP::Enum::Side::LEFT)
        ->build();
}

StateMachineBuilder* StateMachineBuilder::buildRightVibrator()
{
    m_pStateMachine->m_pRightVibrator = VibratorBuilder()
        .reset()
        ->assignSide(::MaskUP::Enum::Side::RIGHT)
        ->build();
}

StateMachineBuilder* StateMachineBuilder::buildLeftBCHeadPhone()
{
    m_pStateMachine->m_pLeftBCHeadPhone = BCHeadphoneBuilder()
        .reset()
        ->assignSide(::MaskUP::Enum::Side::LEFT)
        ->build();
}

StateMachineBuilder* StateMachineBuilder::buildRightBCHeadPhone()
{
    m_pStateMachine->m_pRightBCHeadPhone = BCHeadphoneBuilder()
        .reset()
        ->assignSide(::MaskUP::Enum::Side::RIGHT)
        ->build();
}

StateMachineBuilder* StateMachineBuilder::buildServomotor()
{
    m_pStateMachine->m_pServomotor = ServoMotorBuilder()
        .reset()
        ->assignDefaultPosition(::MaskUP::Enum::Position::M1000)
        ->build();
}

StateMachineBuilder* StateMachineBuilder::addCallbackFunctions()
{

}

StateMachineBuilder* StateMachineBuilder::setAllowedComponentsToRequest()
{
    m_pStateMachine->setAllowedComponentsToRequest();
}

StateMachineBuilder* StateMachineBuilder::setRequiredComponentsToStart()
{
    m_pStateMachine->setRequiredComponentsToStart();
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

}
}
