/*
 * Created on Mon Aug 26 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUP
 */

#pragma once

#include "Json.hpp"
#include "ICommunication.h"
#include "IResponse.h"
#include "BluetoothSerial.h"
#include <Arduino.h>
#include <string>

namespace MaskUP
{
namespace Communication
{

class BluetoothManager final : public ICommunication, public IResponse
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

    void processNotOkResponse(Enum::ReturnValue inReturnValue) override;

    void processRequestResponse(Enum::ReturnValue inReturnValue) override;
    void processRequestResponse(Enum::ReturnValue inReturnValue, Enum::Request inRequest, String value) override;
    void processRequestResponse(Enum::ReturnValue inReturnValue, Enum::Request inRequest, uint32_t value) override;

    void sendData(String jsonDoc);
    bool isAQryCmd(const String& inData);
    BluetoothSerial SerialBT;


};
}
}