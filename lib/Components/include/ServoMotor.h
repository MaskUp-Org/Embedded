/*
 * Created on Sat Jun 29 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#pragma once

#include "IComponent.h"
#include "Enums.h"
#include <ESP32Servo.h>
#include <memory>

namespace MaskUP
{
namespace Component
{

class ServoMotor : public IComponent
{
public:

    ServoMotor();
    ~ServoMotor();

    virtual void setup(uint8_t inPin, uint8_t inMode) = 0;
    void setup(uint8_t inPin);


    /**
     * @brief Run the component.
     *
     */
    virtual void run() = 0;

    /**
    * @brief Stop the component
    *
    */
    virtual void stop() = 0;

    void changePosition(const ::MaskUP::Enum::Position inPosition);


private:
    ::MaskUP::Enum::Position m_position;
    std::unique_ptr <Servo> m_pServo;
};

}
}