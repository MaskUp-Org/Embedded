#include <unity.h>  // Import the Unity module

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

std::shared_ptr <::MaskUP::StateMachine::StateMachine> pStateMachine;
std::shared_ptr <::MaskUP::Communication::EmergencyButton> pEmergencyButton;
std::shared_ptr <::MaskUP::Communication::BluetoothManager> pBluetoothManager;

// StateMachine creation test
void test_create_state_machine(void) {
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

    TEST_ASSERT_NOT_NULL(pStateMachine);  
}

// EmergencyButton creation test
void test_create_emergency_button(void) {
    uint8_t emergencyButtonPin = 2;
    pEmergencyButton = ::MaskUP::Build::EmergencyButtonBuilder()
        .reset()
        ->setup(emergencyButtonPin, INPUT_PULLUP)
        ->buildStateMachine(pStateMachine)
        ->build();

    TEST_ASSERT_NOT_NULL(pEmergencyButton);  
    TEST_ASSERT_EQUAL(emergencyButtonPin, pEmergencyButton->getPin()); 
}

// BluetoothManager creation test
void test_create_bluetooth_manager(void) {
    uint32_t serialValue = 115200;
    pBluetoothManager = ::MaskUP::Build::BluetoothManagerBuilder()
        .reset()
        ->setup(serialValue)
        ->build();

    TEST_ASSERT_NOT_NULL(pBluetoothManager);  
}
// Unity setup
void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_create_state_machine);
    RUN_TEST(test_create_emergency_button);
    RUN_TEST(test_create_bluetooth_manager);

    UNITY_END();
}

void loop() {
}
