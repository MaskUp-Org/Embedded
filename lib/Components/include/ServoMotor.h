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

class ServoMotor final : public IComponent
{
public:

    ServoMotor();
    //~ServoMotor();

    virtual void setup(uint8_t, uint8_t) {};
    void setup(uint8_t inPin);


    /**
     * @brief Run the component.
     *
     */
    virtual void run() {};

    /**
    * @brief Stop the component
    *
    */
    virtual void stop() {};

    void changePosition(const ::MaskUP::Enum::Position inPosition);


private:
    ::MaskUP::Enum::Position m_position;
    std::unique_ptr <Servo> m_pServo;
};

}
}