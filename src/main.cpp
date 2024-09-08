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
    String devicename = ::MaskUP::Tools::getDeviceInformation("DeviceName");

    pStateMachine = ::MaskUP::Build::StateMachineBuilder()
                    .reset ()
                    ->setRequiredComponentsToStart()
                    ->setMandatoryComponents()
                    ->setAllowedComponentsToRequest()
                    ->buildESP32()
                    ->buildLeftVibrator()
                    ->buildRightVibrator()
                    ->buildServomotor()
                    ->build();

    pEmergencyButton = ::MaskUP::Build::EmergencyButtonBuilder()
                       .reset()
                       ->setup(emergencyButtonPin, INPUT_PULLUP)
                       ->buildStateMachine(pStateMachine)
                       ->build();

    pBluetoothManager = ::MaskUP::Build::BluetoothManagerBuilder()
                        .reset()
                        ->setup(serialValue)
                        ->build();
}

void loop()
{

}