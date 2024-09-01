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

        void BluetoothManager::manageBluetoothData()
        {

            String jsonData = "";

            while (SerialBT.available())
            {
                char c = SerialBT.read();
                jsonData += c;
            }

            JsonDocument doc;
            DeserializationError error = deserializeJson(doc, jsonData);

            if (error)
            {
                Serial.print("Erreur de désérialisation: ");
                Serial.println(error.c_str());
                return;
            }
            processIncomingJsonData(doc);
        }


        void BluetoothManager::processIncomingJsonData(JsonDocument jsonDoc)
        {

            Type type = typeFromString(jsonDoc["type"]);
            Actions action = actionsFromString(jsonDoc["action"]);

            switch (type)
            {
            case Type::COMMAND:

                switch (action)
                {
                case Actions::SET_ALTITUDE:
                {
                    int value = jsonDoc["data"]["value"];
                    processIncomingRequest(action, value);
                    break;
                }

                case Actions::SET_DEVICE_NAME:
                case Actions::SET_VERSION:
                case Actions::DIRECTION:
                {
                    const char *value = jsonDoc["data"]["value"];
                    processIncomingRequest(action, value);
                    break;
                }

                case Actions::RUN_SOUND:
                case Actions::STOP_SOUND:
                case Actions::UNKNOWN:
                    processIncomingRequest(action);
                    break;

                default:
                    break;
                }
                break;

            case Type::QUERY:
                processIncomingRequest(action);
                break;

            default:
                break;
            }
        }


        void BluetoothManager::processIncomingRequest(const Actions action)
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
                request(Enum::Component::LEFTBCHEADPHONE, Enum::Request::STOP_SOUND);
                request(Enum::Component::RIGHTBCHEADPHONE, Enum::Request::STOP_SOUND);
                break;

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

        void BluetoothManager::processIncomingRequest(const Actions action, const int value)
        {
            switch (action)
            {
            case Actions::SET_ALTITUDE:
            {

                Enum::Position position = Enum::positionFromInt(value);
                request(Enum::Component::SERVOMOTOR, Enum::Request::CHANGE_POSITION, position);
                break;
            }

            case Actions::DIRECTION:
                request(Enum::Component::SERVOMOTOR, Enum::Request::RUN_VIBRATOR, value);
                break;

            case Actions::UNKNOWN:
            default:
                request(Enum::Component::UNKNOWN, Enum::Request::UNKNOWN);
                break;
            }
        }

        void BluetoothManager::processIncomingRequest(const Actions action, const std::string &value)
        {

            switch (action)
            {

            case Actions::DIRECTION:
            {

                if (value == "left")
                    request(Enum::Component::SERVOMOTOR, Enum::Request::RUN_VIBRATOR, ::MaskUP::Enum::Side::LEFT);

                else if (value == "right")
                    request(Enum::Component::SERVOMOTOR, Enum::Request::RUN_VIBRATOR, ::MaskUP::Enum::Side::RIGHT);

                break;
            }
            case Actions::UNKNOWN:
            default:
            {
                request(Enum::Component::UNKNOWN, Enum::Request::UNKNOWN);
                break;
            }
            }
        }


        void BluetoothManager::processNotOkResponse(Enum::ReturnValue inReturnValue)
        {
            JsonDocument jsonDoc;

            switch (inReturnValue)
            {

            case Enum::ReturnValue::ERROR_OCCURED:
                jsonDoc["type"] = "response";
                jsonDoc["status"] = "error";
                jsonDoc["message"] = "Erreur lors du traitement de la commande.";
                break;
            case Enum::ReturnValue::COMPONENT_NOT_FOUND:
                jsonDoc["type"] = "response";
                jsonDoc["status"] = "error";
                jsonDoc["message"] = "Composant non trouvé.";
                break;
            case Enum::ReturnValue::COMPONENT_NOT_ALLOWED:
                jsonDoc["type"] = "response";
                jsonDoc["status"] = "error";
                jsonDoc["message"] = "Composant non autorisé.";
                break;
            case Enum::ReturnValue::INVALID_POINTER:
                jsonDoc["type"] = "response";
                jsonDoc["status"] = "error";
                jsonDoc["message"] = "Pointeur invalide.";
                break;
            case Enum::ReturnValue::EMPTY_QUEUE:
                jsonDoc["type"] = "response";
                jsonDoc["status"] = "error";
                jsonDoc["message"] = "File vide.";
                break;

            case Enum::ReturnValue::EMPTY_REQUEST:
                jsonDoc["type"] = "response";
                jsonDoc["status"] = "error";
                jsonDoc["message"] = "Requête vide.";
                break;

            default:
                jsonDoc["type"] = "response";
                jsonDoc["status"] = "unknown";
                jsonDoc["message"] = "Requete inconnue.";
                jsonDoc["data"]["value"] = "N/A";
                break;
            }

            sendJsonData(jsonDoc);
            return;
        }


        void BluetoothManager::processRequestResponse(Enum::ReturnValue inReturnValue)
        {
            if (inReturnValue == Enum::ReturnValue::OK)
            {
                JsonDocument jsonDoc;

                jsonDoc["type"] = "response";
                jsonDoc["status"] = "success";
                jsonDoc["message"] = "Commande traitée avec succès.";

                sendJsonData(jsonDoc);
            }
            else
            {

                processNotOkResponse(inReturnValue);
            }

            return;
        }
    
        void BluetoothManager::processRequestResponse(Enum::ReturnValue inReturnValue, Enum::Request inRequest, std::string &value)
        {
            if (inReturnValue == Enum::ReturnValue::OK)
            {
                JsonDocument jsonDoc;

                switch (inRequest)
                {
                case Enum::Request::GET_DEVICE_VERSION:
                    jsonDoc["type"] = "response";
                    jsonDoc["status"] = "success";
                    jsonDoc["message"] = "Device Version";
                    jsonDoc["data"]["value"] = value;
                    break;
                case Enum::Request::GET_DEVICE_NAME:
                    jsonDoc["type"] = "response";
                    jsonDoc["status"] = "success";
                    jsonDoc["message"] = "Device Name";
                    jsonDoc["data"]["value"] = value;
                    break;

                default:
                    jsonDoc["type"] = "response";
                    jsonDoc["status"] = "unknown";
                    jsonDoc["message"] = "Requete inconnue.";
                    jsonDoc["data"]["value"] = "N/A";
                    break;
                }
                sendJsonData(jsonDoc);
            }
            else
            {
                processNotOkResponse(inReturnValue);
            }
        }

        void BluetoothManager::processRequestResponse(Enum::ReturnValue inReturnValue, Enum::Request inRequest, u_int32_t value)
        {
            if (inReturnValue == Enum::ReturnValue::OK)
            {
                JsonDocument jsonDoc;
                switch (inRequest)
                {
                case Enum::Request::GET_BATTERY_PERCENTAGE:
                    jsonDoc["type"] = "response";
                    jsonDoc["status"] = "success";
                    jsonDoc["message"] = "Battery Level";
                    jsonDoc["data"]["value"] = value;
                    break;
                case Enum::Request::GET_POSITION:
                    jsonDoc["type"] = "response";
                    jsonDoc["status"] = "success";
                    jsonDoc["message"] = "Position";
                    jsonDoc["data"]["value"] = value;
                    break;

                default:
                    jsonDoc["type"] = "response";
                    jsonDoc["status"] = "unknown";
                    jsonDoc["message"] = "Requete inconnue.";
                    jsonDoc["data"]["value"] = "N/A";
                    break;
                }
                sendJsonData(jsonDoc);
            }
            else
            {
                processNotOkResponse(inReturnValue);
            }
        }


        void BluetoothManager::sendJsonData(JsonDocument jsonDoc)
        {
            String jsonString;
            serializeJson(jsonDoc, jsonString);
            SerialBT.println(jsonString);
            Serial.println("Message envoyé : " + jsonString);
            return;
        }

    }
}
