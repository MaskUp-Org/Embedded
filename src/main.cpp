/*
 * Created on Sat Feb 25 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */

#include "StateMachineBuilder.h"
#include "EmergencyButtonBuilder.h"
#include "BluetoothManagerBuilder.h"


#include "StateMachine.h"
#include "EmergencyButton.h"
#include "BluetoothManager.h"

#include "FileReader.h"

#include <Arduino.h>
#include <memory>
#include <stdexcept>

 //Those three objects will manage everything
std::shared_ptr <::MaskUP::StateMachine::StateMachine> pStateMachine;
std::shared_ptr <::MaskUP::Communication::EmergencyButton> pEmergencyButton;
std::shared_ptr <::MaskUP::Communication::BluetoothManager> pBluetoothManager;


void setup()
{
    //////////// Can modify those values /////////////
    uint8_t emergencyButtonPin = 0;
    uint32_t serialValue = 115200;
    //////////////////////////////////////////////////
    Serial.begin(serialValue);
    Serial.println("Start");
    if (!LittleFS.begin()) {
        Serial.println("LittleFS cannot begin.");
    }
    else {
        Serial.println("LittleFS begin.");
    }
    Serial.println("getDeviceInfos");

    String devicename = ::MaskUP::Tools::getDeviceInformation("/DeviceName");
    Serial.println("Build StateMachine");
    auto stateMachineBuilder = ::MaskUP::Build::StateMachineBuilder();
    Serial.println("statemachineBuilder ::: reset");
    stateMachineBuilder.reset();

    Serial.println("statemachineBuilder ::: setRequiredComponentsToStart");
    stateMachineBuilder.setRequiredComponentsToStart();

    Serial.println("statemachineBuilder ::: setMandatoryComponents");
    stateMachineBuilder.setMandatoryComponents();

    Serial.println("statemachineBuilder ::: setAllowedComponentsToRequest");
    stateMachineBuilder.setAllowedComponentsToRequest();

    Serial.println("statemachineBuilder ::: buildESP32");
    stateMachineBuilder.buildESP32();

    Serial.println("statemachineBuilder ::: buildLeftVibrator");
    stateMachineBuilder.buildLeftVibrator();

    Serial.println("statemachineBuilder ::: buildRightVibrator");
    stateMachineBuilder.buildRightVibrator();

    Serial.println("statemachineBuilder ::: buildServomotor");
    stateMachineBuilder.buildServomotor();

    Serial.println("statemachineBuilder ::: Build");
    pStateMachine = stateMachineBuilder.build();

    if (pStateMachine == nullptr)
    {
        Serial.println("StateMachine not found.");
    }

    Serial.println("Build EmergencyButton");
    pEmergencyButton = ::MaskUP::Build::EmergencyButtonBuilder()
        .reset()
        ->setup(emergencyButtonPin, INPUT_PULLUP)
        ->buildStateMachine(pStateMachine)
        ->build();
    if (pEmergencyButton == nullptr)
    {
        Serial.println("EmergencyButton not found.");
    }

    Serial.println("Build BluetoothManager");
    pBluetoothManager = ::MaskUP::Build::BluetoothManagerBuilder()
        .reset()
        ->setup(serialValue)
        ->build();
    if (pBluetoothManager == nullptr)
    {
        Serial.println("BluetoothManager not found.");
    }
    // }
    // catch (const std::exception& e)
    // {
    //     Serial.println("--- Exception ---");
    //     Serial.println(e.what());
    //     Serial.println("--- ------ ---");
    // }


}

void loop()
{
    Serial.println("Hello");
    delay(1000);
}