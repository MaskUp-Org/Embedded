/*
 * Created on Sat Jun 29 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#pragma once

#include "IComponent.h"
#include "Enums.h"
 // #include <ESP32Servo.h>
#include <memory>

namespace MaskUP
{
namespace Component
{

class ServoMotor final : public IComponent
{
public:

    ServoMotor();

    virtual void setup(uint8_t, uint8_t) {};
    void setup();


    void setFrequency(const uint8_t inFrequency);
    void setResolution(const uint8_t inResolution);
    void setId(const uint8_t inId);
    void setPin(const uint8_t inPin);


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

    ::MaskUP::Enum::Position getPosition();


private:
    ::MaskUP::Enum::Position m_position;
    // std::unique_ptr <Servo> m_pServo;
    uint8_t m_servoFrequency;
    uint8_t m_servoResolution;
    uint8_t m_servoId;
    uint8_t m_pin;

    // #define FREQUENCE_SERVO 50
    // #define FREQUENCE_ID 1
    // #define RESOLUTION_SERVO 12
};

}
}