/*
 * Created on Wed Sep 04 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#pragma once

#include "IComponent.h"

#include <memory>

namespace MaskUP
{
namespace Component
{

class Battery : public IComponent
{
public:

    /**
     * @brief Setup the component
     * @param inPin : Pin number physically connected to the component
     * @param inMode : INPUT or OUTPUT
     *
     */
    virtual void setup(uint8_t inPin, uint8_t inMode);

    int getBatteryPercentage();


};

}
}