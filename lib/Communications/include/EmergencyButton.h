/*
 * Created on Sat Jun 29 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUP
 */

#pragma once

#include "StateMachine.h"
#include "ICommunication.hpp"

#include <memory>

namespace MaskUP
{
namespace Communication
{

class EmergencyButton : public ICommunication
{
public:

    /**
     * @brief Setup the component
     * @param inPin : Pin number physically connected to the component
     * @param inMode : INPUT or OUTPUT
     *
     */
    void setup(uint8_t inPin, uint8_t inMode);


};

}
}