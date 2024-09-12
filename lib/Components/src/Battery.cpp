/*
 * Created on Wed Sep 04 2024
 *
 * Copyright (c) 2024 MaskUP
 */

#include "Battery.h"
#include <iostream>

namespace MaskUP
{
namespace Component
{

void Battery::setup(uint8_t inPin, uint8_t inMode)
{
    pinMode(inPin, inMode);
}


int Battery::getBatteryPercentage()
{
    Serial.println("Enter function : Battery::getBatteryPercentage");
    float v_mes = analogRead(35);
    float v_dc = 1.435 * (v_mes / 4095) * 3.3;
    int ret = static_cast<int> (round(v_dc));
    Serial.println("Left function : Battery::getBatteryPercentage");
    return ret;
}

}
}