/*
 * Created on Mon Feb 26 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#pragma once

#include "IComponent.h"

namespace MaskUP
{
namespace Component
{

class Vibrator final : public IComponent
{
public:

    Vibrator();
    ~Vibrator() {};

    /**
     * @brief Setup the component
     * @param inPin : Pin number physically connected to the component
     * @param inMode : INPUT or OUTPUT
     *
     */
    virtual void setup(uint8_t inPin, uint8_t inMode) override;


    /**
     * @brief Run the component.
     *
     */
    virtual void run() override;

    /**
    * @brief Stop the component
    *
    */
    virtual void stop() override;

    void setSide(::MaskUP::Enum::Side inSide);

private:
    ::MaskUP::Enum::Side m_side;
    uint8_t m_pin;
};

}
}