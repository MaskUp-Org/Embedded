/*
 * Created on Sat Feb 25 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */



#include <Arduino.h>
 //#include "StateMachine.h"
 //#include "EmergencyButton.h"
#include "BluetoothManager.h"
// #include "ServoMotor.h"
// #include <vector>
// #include "IComponent.h"
// #include "BCHeadphone.h"
// #include "HardwareSerial.h"

MaskUP::Communication::BluetoothManager bluetoothManager;



void setup() {
    Serial.begin(115200);

    // bluetoothManager.setup();

}

void loop() {
    bluetoothManager.loop();
}