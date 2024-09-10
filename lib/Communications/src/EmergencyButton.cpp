/*
 * Created on Mon Feb 26 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#include "EmergencyButton.h"
#include <iostream>
#include <Arduino.h>
namespace MaskUP
{
namespace Communication
{

void emergencyButtonIrqHandler()
{

}
EmergencyButton::EmergencyButton() :
    m_lastButtonState(HIGH),
    m_pin(0)
{}


uint8_t EmergencyButton::getPin()
{
    return m_pin;
}

// Emergency button has to be in the main loop, watching for the user to press it, or using an irq (interruption Request, CPU boring stuff)
void EmergencyButton::setup(uint8_t inPin, uint8_t inMode)
{
    //inmode = INPUT_PULLUP in all cases (i mean, litteraly), but i let you the choice
    pinMode(inPin, inMode);
    m_pin = inPin;
}

void EmergencyButton::run()
{
    // Read the the button state
    // int16_t currentButtonState = digitalRead(m_pin);

    // if (m_lastButtonState == LOW && currentButtonState == HIGH)
    // {
        // too much enum, i know yes, but i really love enums
    request(::MaskUP::Enum::Component::SERVOMOTOR, ::MaskUP::Enum::Request::CHANGE_POSITION, ::MaskUP::Enum::Position::M1000, ::MaskUP::Enum::Caller::EMERGENCYBUTTON);
}

// m_lastButtonState = currentButtonState;
// }



}
}