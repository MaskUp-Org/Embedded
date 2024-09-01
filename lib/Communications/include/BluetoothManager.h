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

    void processIncomingJsonData(JsonDocument jsonDoc);

    void processRequest(Actions action);
    void processRequest(Actions action, const int value);
    void processRequest(Actions action, const std::string& value);

    void proccessResponse(Enum::ReturnValue inReturnValue);
    void proccessResponse(Enum::ReturnValue inReturnValue, Actions action, std::string& value);
    void proccessResponse(Enum::ReturnValue inReturnValue, Actions action);


    bool m_state;

    BluetoothSerial SerialBT;


};
}
}