/*
 * Created on Mon Aug 26 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUP
 */

#pragma once

#include "Json.hpp"
#include "ICommunication.h"
#include "BluetoothSerial.h"
#include <Arduino.h>
#include <string>

namespace MaskUP
{
namespace Communication
{

class BluetoothManager final : public ICommunication
{
public:

    BluetoothManager();

    /**
     * @brief Setup the component
     * @param inPin : Pin number physically connected to the component
     * @param inMode : INPUT or OUTPUT
     *
     */
    void setup(const uint32_t inSerial, const String& inBTDeviceName);
    void loop();



private:
    void manageBluetoothData();

    void processIncomingData(String incomingData);

    void processNotOkResponse(Enum::ReturnValue inReturnValue);

    void processRequestResponse(Enum::ReturnValue inReturnValue);
    void processRequestResponse(Enum::ReturnValue inReturnValue, Enum::Request inRequest, String value);
    void processRequestResponse(Enum::ReturnValue inReturnValue, Enum::Request inRequest, uint32_t value);

    void sendData(String jsonDoc);


    BluetoothSerial SerialBT;


};
}
}