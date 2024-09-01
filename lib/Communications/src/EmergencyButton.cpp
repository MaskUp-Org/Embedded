/*
 * Created on Mon Feb 26 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#include "EmergencyButton.h"
#include <iostream>

namespace MaskUP
{
namespace Communication
{

void EmergencyButton::setup(uint8_t inPin, uint8_t inMode)
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