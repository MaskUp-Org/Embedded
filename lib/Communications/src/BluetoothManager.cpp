#include "BluetoothManager.h"
#include "Enums.h"
#include <mutex>
#include <thread>
namespace MaskUP
{
namespace Communication
{
std::mutex btMutex;

BluetoothManager::BluetoothManager() :
    ICommunication()
{

}

void BluetoothManager::setup(const uint32_t inSerial, const String& inBTDeviceName)
{
    // 115200
    Serial.begin(inSerial);
    SerialBT.begin(inBTDeviceName);
    Serial.println(inBTDeviceName);

    Serial.println("Bluetooth prêt");
}

void BluetoothManager::loop()
{
    while ("MaskUp")
    {
        if (SerialBT.available())
        {
            manageBluetoothData();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

bool BluetoothManager::isAQryCmd(const String& inData)
{
    int firstColon = inData.indexOf(':');
    int secondColon = inData.indexOf(':', firstColon + 1);

    String stringType = inData.substring(0, firstColon);
    String stingAction = (secondColon != -1) ? inData.substring(firstColon + 1, secondColon) : inData.substring(firstColon + 1);
    String value = (secondColon != -1) ? inData.substring(secondColon + 1) : "";

    ::MaskUP::Enum::Type type = ::MaskUP::Enum::typeFromString(stringType);
    ::MaskUP::Enum::Action action = ::MaskUP::Enum::actionFromString(stingAction);
    if (type != ::MaskUP::Enum::Type::END
        || type != ::MaskUP::Enum::Type::UNKNOWN
        || action != ::MaskUP::Enum::Action::UNKNOWN
        || action != ::MaskUP::Enum::Action::UNKNOWN
        )
    {
        return true;

    }
    return false;
}


void BluetoothManager::manageBluetoothData()
{
    // std::lock_guard<std::mutex> lock(btMutex);
    static String incomingData = "";

    while (SerialBT.available())
    {
        char c = SerialBT.read();
        if (c != '\n')
        {
            incomingData += c;
        }
        c = 0;
    }
    if (!incomingData.isEmpty() && isAQryCmd(incomingData))
    {
        Serial.print("Data received : ");
        Serial.println(incomingData);
        processIncomingData(incomingData);
        incomingData.clear();
    }
}



void BluetoothManager::processIncomingData(String message)
{
    Serial.println("Enter function : BluetoothManager::processIncomingData");
    // Messages :
    //      CMD:DIRECTION:LEFT             RSP:OK                   RSP:ERROR_OCCURED
    //      CMD:DIRECTION:RIGHT            RSP:OK                   RSP:COMPONENT_NOT_FOUND
    //      CMD:SET_ALTITUDE:1000          RSP:OK                   RSP:COMPONENT_NOT_ALLOWED
    //      CMD:SET_VERISON:1.5.3          RSP:OK                   RSP:INVALID_POINTER
    //      CMD:SET_DEVICE_NAME:MaskUP     RSP:OK                   RSP:EMPTY_QUEUE
    //      CMD:STOP_SOUND                 RSP:OK                   RSP:EMPTY_REQUEST
    //      CMD:RUN_SOUND                  RSP:OK                   RSP:UNKNOWN
    //      CMD:RESET                      RSP:OK
    //      QRY:GET_BATTERY_PERCENTAGE     RSP:OK:85
    //      QRY:GET_ALTITUDE               RSP:OK:1000
    //      QRY:GET_VERSION                RSP:OK:1.5.3
    //      QRY:GET_DEVICE_NAME            RSP:OK:MaskUP

    if (message.length() == 0)
    {
        Serial.println("Message invalide");
        Serial.println("Left function : BluetoothManager::processIncomingData");
        return;
    }

    int firstColon = message.indexOf(':');
    int secondColon = message.indexOf(':', firstColon + 1);

    String stringType = message.substring(0, firstColon);
    String stingAction = (secondColon != -1) ? message.substring(firstColon + 1, secondColon) : message.substring(firstColon + 1);
    stingAction.trim();
    String value = (secondColon != -1) ? message.substring(secondColon + 1) : "";

    ::MaskUP::Enum::Type type = ::MaskUP::Enum::typeFromString(stringType);
    ::MaskUP::Enum::Action action = ::MaskUP::Enum::actionFromString(stingAction);

    if (type == ::MaskUP::Enum::Type::COMMAND)
    {
        switch (action)
        {
        case ::MaskUP::Enum::Action::RUN_SOUND:
        {
            request(Enum::Component::LEFTBCHEADPHONE, Enum::Request::PLAY_SOUND);
            request(Enum::Component::RIGHTBCHEADPHONE, Enum::Request::PLAY_SOUND);
            break;
        }
        case ::MaskUP::Enum::Action::STOP_SOUND:
        {

            request(::MaskUP::Enum::Component::LEFTBCHEADPHONE, ::MaskUP::Enum::Request::STOP_SOUND);
            request(::MaskUP::Enum::Component::RIGHTBCHEADPHONE, ::MaskUP::Enum::Request::STOP_SOUND);
            break;
        }
        case ::MaskUP::Enum::Action::SET_ALTITUDE:
        {
            Serial.println("Request Value = " + value);
            Enum::Position position = Enum::positionFromString(value);
            request(Enum::Component::SERVOMOTOR, ::MaskUP::Enum::Request::CHANGE_POSITION, position, ::MaskUP::Enum::Caller::BLUETOOTH);
            break;
        }
        case ::MaskUP::Enum::Action::DIRECTION:
        {

            if (value == "LEFT")
                request(Enum::Component::LEFTVIBRATOR, ::MaskUP::Enum::Request::RUN_VIBRATOR, ::MaskUP::Enum::Side::LEFT);

            else if (value == "RIGHT")
                request(Enum::Component::RIGHTVIBRATOR, ::MaskUP::Enum::Request::RUN_VIBRATOR, ::MaskUP::Enum::Side::RIGHT);

            break;
        }
        case ::MaskUP::Enum::Action::SET_DEVICE_NAME:
        {
            request(::MaskUP::Enum::Component::ESP_32, ::MaskUP::Enum::Request::CHANGE_DEVICE_NAME, value);
            break;
        }
        case ::MaskUP::Enum::Action::SET_VERSION:
        {
            request(::MaskUP::Enum::Component::ESP_32, ::MaskUP::Enum::Request::CHANGE_DEVICE_VERSION, value);
            break;
        }
        case ::MaskUP::Enum::Action::RESET:
        {
            request(::MaskUP::Enum::Component::ESP_32, ::MaskUP::Enum::Request::RESET);
            break;
        }
        case ::MaskUP::Enum::Action::UNKNOWN:
        default:
            request(::MaskUP::Enum::Component::UNKNOWN, ::MaskUP::Enum::Request::UNKNOWN);
            break;
        }
    }
    else if (type == ::MaskUP::Enum::Type::QUERY)
    {
        Serial.println("processIncomingData::Query : " + static_cast<int>(action));

        switch (action)
        {
        case ::MaskUP::Enum::Action::GET_DEVICE_NAME:
            request(Enum::Component::ESP_32, Enum::Request::GET_DEVICE_NAME);
            break;
        case ::MaskUP::Enum::Action::GET_BATTERY_PERCENTAGE:
            request(Enum::Component::BATTERY, Enum::Request::GET_BATTERY_PERCENTAGE);
            break;
        case ::MaskUP::Enum::Action::GET_ALTITUDE:
            request(Enum::Component::SERVOMOTOR, Enum::Request::GET_POSITION);
            break;
        case ::MaskUP::Enum::Action::GET_VERSION:
            request(Enum::Component::ESP_32, Enum::Request::GET_DEVICE_VERSION);
            break;
        case ::MaskUP::Enum::Action::UNKNOWN:
        default:
            Serial.println("Error occured.");
            break;
        }
    }
    // m_pStateMachine->unlock();
    Serial.println("Left function : BluetoothManager::processIncomingData");
}


void BluetoothManager::processNotOkResponse(::MaskUP::Enum::ReturnValue inReturnValue)
{
    Serial.println("Enter function : BluetoothManager::processNotOkResponse");
    String response = "RSP:UNKNOWN";
    switch (inReturnValue)
    {

    case ::MaskUP::Enum::ReturnValue::ERROR_OCCURED:
        response = "RSP:ERROR_OCCURED";
        break;
    case ::MaskUP::Enum::ReturnValue::COMPONENT_NOT_FOUND:
        response = "RSP:COMPONENT_NOT_FOUND";
        break;
    case ::MaskUP::Enum::ReturnValue::COMPONENT_NOT_ALLOWED:
        response = "RSP:COMPONENT_NOT_ALLOWED";
        break;
    case ::MaskUP::Enum::ReturnValue::INVALID_POINTER:
        response = "RSP:INVALID_POINTER";
        break;
    case ::MaskUP::Enum::ReturnValue::EMPTY_QUEUE:
        response = "RSP:EMPTY_QUEUE";
        break;

    case ::MaskUP::Enum::ReturnValue::EMPTY_REQUEST:
        response = "RSP:EMPTY_REQUEST";
        break;

    case ::MaskUP::Enum::ReturnValue::UNKNOWN:
    default:
        response = "RSP:UNKNOWN";
        break;
    }
    sendData(response);
    return;
    Serial.println("Left function : BluetoothManager::processNotOkResponse");
}

void BluetoothManager::processRequestResponse(::MaskUP::Enum::ReturnValue inReturnValue)
{
    Serial.println("Enter function : BluetoothManager::processRequestResponse");
    if (inReturnValue == ::MaskUP::Enum::ReturnValue::OK)
    {
        String response = "RSP:OK";

        sendData(response);
    }
    else
    {
        processNotOkResponse(inReturnValue);
    }

    return;
    Serial.println("Left function : BluetoothManager::processRequestResponse");
}

void BluetoothManager::processRequestResponse(::MaskUP::Enum::ReturnValue inReturnValue, ::MaskUP::Enum::Request inRequest, String value)
{
    Serial.println("Enter function : BluetoothManager::processRequestResponse");
    if (inReturnValue == ::MaskUP::Enum::ReturnValue::OK)
    {
        String response = "RSP:UNKNOWN";

        switch (inRequest)
        {
        case ::MaskUP::Enum::Request::GET_DEVICE_VERSION:
            response = "RSP:OK:DEVICEVERSION:" + value;
            break;
        case ::MaskUP::Enum::Request::GET_DEVICE_NAME:
            response = "RSP:OK:DEVICENAME:" + value;
            break;

        default:
            response = "RSP:UNKNOWN";
            break;
        }
        sendData(response);
    }
    else
    {
        processNotOkResponse(inReturnValue);
    }
    Serial.println("Left function : BluetoothManager::processRequestResponse");
}

void BluetoothManager::processRequestResponse(::MaskUP::Enum::ReturnValue inReturnValue, ::MaskUP::Enum::Request inRequest, uint32_t value)
{
    Serial.println("Enter function : BluetoothManager::processRequestResponse");
    if (inReturnValue == ::MaskUP::Enum::ReturnValue::OK)
    {
        String response = "RSP:UNKNOWN";
        switch (inRequest)
        {
        case ::MaskUP::Enum::Request::GET_BATTERY_PERCENTAGE:
            response = "RSP:OK:BATTERYPERCENTAGE:" + String(value);
            break;
        case ::MaskUP::Enum::Request::GET_POSITION:
            response = "RSP:OK:SERVOMOTORPOSITION:" + String(value);
            break;

        default:
            response = "RSP:UNKNOWN";
            break;
        }
        sendData(response);
    }
    else
    {
        processNotOkResponse(inReturnValue);
    }
    Serial.println("Left function : BluetoothManager::processRequestResponse");
}

void BluetoothManager::sendData(String data)
{
    Serial.println("Message va être envoyé" + data);
    SerialBT.println(data);
    Serial.println("Message envoyé : " + data);
    return;
}

}
}
