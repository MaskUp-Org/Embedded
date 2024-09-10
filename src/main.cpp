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
#include <thread>


 //Those three objects will manage everything
std::shared_ptr <::MaskUP::StateMachine::StateMachine> pStateMachine;
std::shared_ptr <::MaskUP::Communication::EmergencyButton> pEmergencyButton;
std::shared_ptr <::MaskUP::Communication::BluetoothManager> pBluetoothManager;

// IRQ Manager, as we have a button, we have to work with the possibility of multiple requests in a row.
bool irqReq = false;
#define DEBOUNCE_DELAY 50
uint64_t lastInterruptTime = 0;

void ebIrq() {
    uint64_t currentTime = millis();
    if ((currentTime - lastInterruptTime) > DEBOUNCE_DELAY) {
        irqReq = true;
    }
    lastInterruptTime = currentTime;
}


void setup()
{
    //////////// Can modify those values /////////////
    uint8_t emergencyButtonPin = 2;
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

    // String devicename = ::MaskUP::Tools::getDeviceInformation("/DeviceName");

    Serial.println("Build StateMachine");
    pStateMachine = ::MaskUP::Build::StateMachineBuilder()
        .reset()
        ->setRequiredComponentsToStart()
        ->setMandatoryComponents()
        ->setAllowedComponentsToRequest()
        ->buildESP32()
        ->buildLeftVibrator()
        ->buildRightVibrator()
        ->buildServomotor()
        ->build();

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

    attachInterrupt(digitalPinToInterrupt(pEmergencyButton->getPin()), ebIrq, FALLING);

    Serial.println("Build BluetoothManager");
    pBluetoothManager = ::MaskUP::Build::BluetoothManagerBuilder()
        .reset()
        ->setup(serialValue)
        ->build();
    if (pBluetoothManager == nullptr)
    {
        Serial.println("BluetoothManager not found.");
    }

}

void loop()
{
    if (irqReq == true)
    {
        pEmergencyButton->run();
        irqReq = false;
    }

    auto btManager = pBluetoothManager;
    std::thread bluetoothThread([btManager]() {
        btManager->loop();
        });

    // Detach the thread to run independently
    bluetoothThread.detach();
}