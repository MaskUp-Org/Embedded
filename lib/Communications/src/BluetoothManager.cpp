#include "BluetoothManager.h"
#include "Request.h"
#include "Position.hpp"
namespace MaskUP
{
    namespace Communication
    {

        void BluetoothManager::setup()
        {

            Serial.begin(115200);
            SerialBT.begin("ESP32test");

            Serial.println("Bluetooth prêt");
            m_state = true;
        }

        void BluetoothManager::loop()
        {

            if (SerialBT.available())
            {
                manageBluetoothData();
            }
        }

        // void BluetoothManager::manageBluetoothData()
        // {
        //     String jsonData = "";
        //     while (SerialBT.available())
        //     {
        //         char c = SerialBT.read();
        //         jsonData += c;
        //     }
        //     JsonDocument doc;
        //     DeserializationError error = deserializeJson(doc, jsonData);
        //     if (error)
        //     {
        //         Serial.print("Erreur de désérialisation: ");
        //         Serial.println(error.c_str());
        //         return;
        //     }
        //     processIncomingJsonData(doc);
        // }

        // void BluetoothManager::processIncomingJsonData(JsonDocument jsonDoc)
        // {
        //     Type type = typeFromString(jsonDoc["type"]);
        //     Actions action = actionsFromString(jsonDoc["action"]);
        //     switch (type)
        //     {
        //     case Type::COMMAND:
        //         switch (action)
        //         {
        //         case Actions::SET_ALTITUDE:
        //         {
        //             int value = jsonDoc["data"]["value"];
        //             processIncomingRequest(action, value);
        //             break;
        //         }
        //         case Actions::SET_DEVICE_NAME:
        //         case Actions::SET_VERSION:
        //         case Actions::DIRECTION:
        //         {
        //             const char *value = jsonDoc["data"]["value"];
        //             processIncomingRequest(action, value);
        //             break;
        //         }
        //         case Actions::RUN_SOUND:
        //         case Actions::STOP_SOUND:
        //         case Actions::UNKNOWN:
        //             processIncomingRequest(action);
        //             break;
        //         default:
        //             break;
        //         }
        //         break;
        //     case Type::QUERY:
        //         processIncomingRequest(action);
        //         break;
        //     default:
        //         break;
        //     }
        // }

        void BluetoothManager::manageBluetoothData()
        {

            String incomingData = "";

            while (SerialBT.available())
            {
                char c = SerialBT.read();
                incomingData += c;
            }

            processIncomingData(incomingData);
        }

        void BluetoothManager::processIncomingData(String message)
        {
            // Messages :
            //      CMD:DIRECTION:LEFT             RSP:OK                   RSP:ERROR_OCCURED
            //      CMD:DIRECTION:RIGHT            RSP:OK                   RSP:COMPONENT_NOT_FOUND
            //      CMD:SET_ALTITUDE:1000          RSP:OK                   RSP:COMPONENT_NOT_ALLOWED
            //      CMD:SET_VERISON:1.5.3          RSP:OK                   RSP:INVALID_POINTER
            //      CMD:SET_DEVICE_NAME:MaskUP     RSP:OK                   RSP:EMPTY_QUEUE
            //      CMD:STOP_SOUND                 RSP:OK                   RSP:EMPTY_REQUEST
            //      CMD:RUN_SOUND                  RSP:OK                   RSP:UNKNOWN
            //      QRY:GET_BATTERY_PERCENTAGE     RSP:OK:85
            //      QRY:GET_ALTITUDE               RSP:OK:1000
            //      QRY:GET_VERSION                RSP:OK:1.5.3
            //      QRY:GET_DEVICE_NAME            RSP:OK:MaskUP

            // TODO: return UNKNOWN request
            if (message.length() == 0)
            {
                Serial.println("Message invalide");
                return;
            }

            int firstColon = message.indexOf(':');
            int secondColon = message.indexOf(':', firstColon + 1);

            String stringType = message.substring(0, firstColon);
            String stingAction = (secondColon != -1) ? message.substring(firstColon + 1, secondColon) : message.substring(firstColon + 1);
            String value = (secondColon != -1) ? message.substring(secondColon + 1) : "";

            Type type = typeFromString(stringType);
            Actions action = actionsFromString(stingAction);

            if (type == Type::COMMAND)
            {
                switch (action)
                {
                case Actions::RUN_SOUND:
                {
                    request(Enum::Component::LEFTBCHEADPHONE, Enum::Request::PLAY_SOUND);
                    request(Enum::Component::RIGHTBCHEADPHONE, Enum::Request::PLAY_SOUND);
                    break;
                }
                case Actions::STOP_SOUND:
                {

                    request(Enum::Component::LEFTBCHEADPHONE, Enum::Request::STOP_SOUND);
                    request(Enum::Component::RIGHTBCHEADPHONE, Enum::Request::STOP_SOUND);
                    break;
                }
                case Actions::SET_ALTITUDE:
                {
                    Enum::Position position = Enum::positionFromString(value);
                    request(Enum::Component::SERVOMOTOR, Enum::Request::CHANGE_POSITION, position);
                    break;
                }
                case Actions::DIRECTION:
                {

                    if (value == "left")
                        request(Enum::Component::SERVOMOTOR, Enum::Request::RUN_VIBRATOR, ::MaskUP::Enum::Side::LEFT);

                    else if (value == "right")
                        request(Enum::Component::SERVOMOTOR, Enum::Request::RUN_VIBRATOR, ::MaskUP::Enum::Side::RIGHT);

                    break;
                }
                case Actions::SET_DEVICE_NAME:
                {
                    request(Enum::Component::ESP_32, Enum::Request::CHANGE_DEVICE_NAME, value);
                    break;
                }
                case Actions::SET_VERSION:
                {
                    request(Enum::Component::ESP_32, Enum::Request::CHANGE_DEVICE_VERSION, value);
                    break;
                }
                case Actions::UNKNOWN:
                default:
                    request(Enum::Component::UNKNOWN, Enum::Request::UNKNOWN);
                    break;
                }

                {
                    Serial.println("Lecture de la musique");
                    // Exécutez l'action pour démarrer la musique
                }
            }
            else if (type == Type::COMMAND)
            {
                switch (action)
                {
                case Actions::GET_DEVICE_NAME:
                    request(Enum::Component::ESP_32, Enum::Request::GET_DEVICE_NAME);
                    break;
                case Actions::GET_BATTERY_PERCENTAGE:
                    request(Enum::Component::BATTERY, Enum::Request::GET_BATTERY_PERCENTAGE);
                    break;
                case Actions::GET_ALTITUDE:
                    request(Enum::Component::SERVOMOTOR, Enum::Request::GET_POSITION);
                    break;
                case Actions::GET_VERSION:
                    request(Enum::Component::ESP_32, Enum::Request::GET_DEVICE_VERSION);
                    break;
                case Actions::UNKNOWN:
                default:
                    request(Enum::Component::UNKNOWN, Enum::Request::UNKNOWN);
                    break;
                }
            }
        }
        

        void BluetoothManager::processNotOkResponse(Enum::ReturnValue inReturnValue)
        {
            String response = "RSP:UNKNOWN";
            switch (inReturnValue)
            {

            case Enum::ReturnValue::ERROR_OCCURED:
                response = "RSP:ERROR_OCCURED";

                break;
            case Enum::ReturnValue::COMPONENT_NOT_FOUND:
                response = "RSP:COMPONENT_NOT_FOUND";
                break;
            case Enum::ReturnValue::COMPONENT_NOT_ALLOWED:
                response = "RSP:COMPONENT_NOT_ALLOWED";
                break;
            case Enum::ReturnValue::INVALID_POINTER:
                response = "RSP:INVALID_POINTER";
                break;
            case Enum::ReturnValue::EMPTY_QUEUE:
                response = "RSP:EMPTY_QUEUE";
                break;

            case Enum::ReturnValue::EMPTY_REQUEST:
                response = "RSP:EMPTY_REQUEST";
                break;
                
            case Enum::ReturnValue::UNKNOWN:   
            default:
                response = "RSP:UNKNOWN";
                break;
            }

            sendData(response);
            return;
        }

        void BluetoothManager::processRequestResponse(Enum::ReturnValue inReturnValue)
        {
            if (inReturnValue == Enum::ReturnValue::OK)
            {
                String response = "RSP:OK";

                sendData(response);
            }
            else
            {

                processNotOkResponse(inReturnValue);
            }

            return;
        }

        void BluetoothManager::processRequestResponse(Enum::ReturnValue inReturnValue, Enum::Request inRequest, String value)
        {
            if (inReturnValue == Enum::ReturnValue::OK)
            {
                String response = "RSP:UNKNOWN";

                switch (inRequest)
                {
                case Enum::Request::GET_DEVICE_VERSION:
                case Enum::Request::GET_DEVICE_NAME:
                    response = "RSP:OK:" + value;
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
        }

        void BluetoothManager::processRequestResponse(Enum::ReturnValue inReturnValue, Enum::Request inRequest, uint32_t value)
        {
            if (inReturnValue == Enum::ReturnValue::OK)
            {
                String response = "RSP:UNKNOWN";
                switch (inRequest)
                {
                case Enum::Request::GET_BATTERY_PERCENTAGE:
                    response = "RSP:OK:" + String(value);
                    break;
                case Enum::Request::GET_POSITION:
                    response = "RSP:OK:" + String(value);
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
        }

        void BluetoothManager::sendData(String data)
        {
            SerialBT.println(data);
            Serial.println("Message envoyé : " + data);
            return;
        }

    }
}
