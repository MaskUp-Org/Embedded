/*
 * Created on Wed Sep 04 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#include "Battery.h"
#include <iostream>

namespace MaskUP
{
namespace Component
{

void Battery::setup(uint8_t inPin, uint8_t inMode)
{
    (void)inPin;
    (void)inMode;
    std::cout << "BCHeadphone::run.\n";
}

// void EmergencyButton::registerStateMachine(std::shared_ptr<::MaskUP::StateMachine::StateMachine> inpStateMachine)
// {
//     m_pStateMachine = inpStateMachine;
// }


}
}