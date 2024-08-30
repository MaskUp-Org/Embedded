/*
 * Created on Sat Feb 25 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */

#pragma once

#include <Arduino.h>
#include "Enums.h"

namespace MaskUP
{
namespace Component
{

class IComponent
{
public:

    /**
     * @brief Setup the component
     * @param inPin : Pin number physically connected to the component
     * @param inMode : INPUT or OUTPUT
     *
     */
    virtual void setup (uint8_t inPin, uint8_t inMode) = 0;

    /**
     * @brief Run the component.
     *
     */
    virtual void run () = 0;

    /**
     * @brief Stop the component
     *
     */
    virtual void stop () = 0;

    ::MaskUP::Enum::State m_state;

};


}
}