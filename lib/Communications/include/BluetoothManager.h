/*
 * Created on Mon Aug 26 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUP
 */

#pragma once

#include <ArduinoJson.h>
#include "Json.hpp"
#include "ICommunication.h"
#include "BluetoothSerial.h"

namespace MaskUP
{
namespace Communication
{

class BluetoothManager final : public ICommunication
{
public:
    /**
     * @brief Setup the component
     * @param inPin : Pin number physically connected to the component
     * @param inMode : INPUT or OUTPUT
     *
     */
    void setup();
    void loop();



private:
    void manageBluetoothData();

    //void processIncomingJsonData(JsonDocument jsonDoc);
    void processIncomingData(String incomingData);

    // void processIncomingRequest(Actions action);
    // void processIncomingRequest(Actions action, const int value);
    // void processIncomingRequest(Actions action, const std::string& value);

    void processNotOkResponse(Enum::ReturnValue inReturnValue);

    void processRequestResponse(Enum::ReturnValue inReturnValue);
    void processRequestResponse(Enum::ReturnValue inReturnValue, Enum::Request inRequest, String value);
    void processRequestResponse(Enum::ReturnValue inReturnValue, Enum::Request inRequest, uint32_t value);

    void sendData(String jsonDoc);

    bool m_state;

    BluetoothSerial SerialBT;


};
}
}