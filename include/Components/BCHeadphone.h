/*
 * Created on Mon Feb 26 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#pragma once

#include "IComponent.h"


namespace MaskUP::Component
{

/// @brief Manage the Bone conducting headphones.
class BCHeadphone : public IComponent
{
public:

    /**
     * @brief Setup the component,
     * @param inPin : Pin number physically connected to the component
     * @param inMode : INPUT or OUTPUT
     *
     */
    virtual void setup (uint8_t inPin, uint8_t inMode) override;
    /**
     * @brief Run the component.
     *
     */
    virtual void run () override;

    /**
    * @brief Stop the component
    *
    */
    virtual void stop () override;

    

};

}
