#include "BluetoothManager.h"
#include "Request.h"
#include "Position.hpp"
namespace MaskUP
{
namespace Communication
{


void BluetoothManager::setup()  {

    Serial.begin(115200);
    SerialBT.begin("ESP32test"); 

    Serial.println("Bluetooth prêt");
    m_state = true;
}

void BluetoothManager::loop()  {

if (SerialBT.available()) {
        manageBluetoothData(); 
    }  
}


void BluetoothManager::manageBluetoothData() {
    
   String jsonData = "";

    while (SerialBT.available()) {
        char c = SerialBT.read(); 
        jsonData += c; 
    }

    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonData);

    if (error) {
        Serial.print("Erreur de désérialisation: ");
        Serial.println(error.c_str());
        return;
    }
    processIncomingJsonData(doc);
}

void BluetoothManager::processIncomingJsonData(StaticJsonDocument<200>& jsonDoc) {
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
                    processRequest(action, value);
                    break;
                }
                
                case Actions::SET_DEVICE_NAME:
                case Actions::SET_VERSION:
                case Actions::DIRECTION:
                {
                    const char* value = jsonDoc["data"]["value"];
                    processRequest(action, value);
                    break;
                }

                case Actions::RUN_SOUND:
                case Actions::STOP_SOUND:
                case Actions::UNKNOWN:
                    processRequest(action);
                    break;
                
                default:
                    break;
            }
            break;

        case Type::QUERY:
            processRequest(action);
            break;

        default:
            break;
    }

}

void BluetoothManager::processRequest(const Actions action) {
    //StateMachine::Request incomingRequest;
    MaskUP::Enum::ReturnValue response = MaskUP::Enum::ReturnValue::UNKNOWN;
    switch (action)
    {
    case Actions::RUN_SOUND:{

        //incomingRequest.m_Component = Enum::Component::LEFTBCHEADPHONE;
        //incomingRequest.m_request = Enum::Request::PLAY_SOUND;
        MaskUP::Enum::ReturnValue firstResp = request(Enum::Component::LEFTBCHEADPHONE, Enum::Request::PLAY_SOUND);
        MaskUP::Enum::ReturnValue secondResp = request(Enum::Component::RIGHTBCHEADPHONE, Enum::Request::PLAY_SOUND);

        if(firstResp == Enum::ReturnValue::OK && secondResp == Enum::ReturnValue::OK)
            response = Enum::ReturnValue::OK;
        else
            response = Enum::ReturnValue::ERROR_OCCURED;
        
        return proccessResponse(response);
        break;
    }

    case Actions::STOP_SOUND:{

        
        MaskUP::Enum::ReturnValue firstResp = request(Enum::Component::LEFTBCHEADPHONE, Enum::Request::STOP_SOUND);
        MaskUP::Enum::ReturnValue secondResp = request(Enum::Component::RIGHTBCHEADPHONE, Enum::Request::STOP_SOUND);
        
        if(firstResp == Enum::ReturnValue::OK && secondResp == Enum::ReturnValue::OK)
            response = Enum::ReturnValue::OK;
        else
            response = Enum::ReturnValue::ERROR_OCCURED;
        
        return proccessResponse(response);
        break;
    }

    case Actions::GET_DEVICE_NAME:
        response = request(Enum::Component::ESP_32, Enum::Request::GET_DEVICE_NAME);
        break;

    case Actions::GET_BATTERY_PERCENTAGE:
        response = request(Enum::Component::BATTERY, Enum::Request::GET_BATTERY_PERCENTAGE);
        break;

    case Actions::GET_ALTITUDE:
        response = request(Enum::Component::SERVOMOTOR, Enum::Request::GET_POSITION);
        break;

    case Actions::GET_VERSION:
        response = request(Enum::Component::ESP_32, Enum::Request::GET_DEVICE_VERSION);
        break;

    case Actions::UNKNOWN:
        response = request(Enum::Component::UNKNOWN, Enum::Request::UNKNOWN);
        break;

    default:
        break;
    }
    
}

void BluetoothManager::processRequest(const Actions action, const int value) {
    MaskUP::Enum::ReturnValue response = MaskUP::Enum::ReturnValue::UNKNOWN;

    switch (action)
    {
    case Actions::SET_ALTITUDE:{

        Enum::Position position = Enum::positionFromInt(value);
        response = request(Enum::Component::SERVOMOTOR, Enum::Request::CHANGE_POSITION, position);
        break;
    }

    case Actions::DIRECTION:
        response = request(Enum::Component::SERVOMOTOR, Enum::Request::RUN_VIBRATOR, value);
        break;

    case Actions::UNKNOWN:
        response = request(Enum::Component::UNKNOWN, Enum::Request::UNKNOWN);
        break;

    default:
        break;
    }

    proccessResponse(response);
}

void BluetoothManager::processRequest(const Actions action, const std::string &value) {
    MaskUP::Enum::ReturnValue response = MaskUP::Enum::ReturnValue::UNKNOWN;

    switch (action)
    {
    
    case Actions::DIRECTION:{

        if(value == "left")
            response = request(Enum::Component::SERVOMOTOR, Enum::Request::RUN_VIBRATOR, 0);

        else if(value == "right")
            response = request(Enum::Component::SERVOMOTOR, Enum::Request::RUN_VIBRATOR, 1);

        break;
    }

    case Actions::UNKNOWN:
    {
        response = request(Enum::Component::UNKNOWN, Enum::Request::UNKNOWN);
        break;

    }
    default:
        break;
    }

    proccessResponse(response);
}

void BluetoothManager::proccessResponse(Enum::ReturnValue inReturnValue){

    StaticJsonDocument<200> jsonDoc;
    
    switch (inReturnValue) {
        case Enum::ReturnValue::OK :
            jsonDoc["type"] = "response";
            jsonDoc["status"] = "success";
            jsonDoc["message"] = "Commande traitée avec succès.";
            break;
        case Enum::ReturnValue::ERROR_OCCURED :
            jsonDoc["type"] = "response";
            jsonDoc["status"] = "error";
            jsonDoc["message"] = "Erreur lors du traitement de la commande.";
            break;
        case Enum::ReturnValue::COMPONENT_NOT_FOUND :
            jsonDoc["type"] = "response";
            jsonDoc["status"] = "error";
            jsonDoc["message"] = "Composant non trouvé.";
            break;
        case Enum::ReturnValue::COMPONENT_NOT_ALLOWED :
            jsonDoc["type"] = "response";
            jsonDoc["status"] = "error";
            jsonDoc["message"] = "Composant non autorisé.";
            break;
        case Enum::ReturnValue::INVALID_POINTER :
            jsonDoc["type"] = "response";
            jsonDoc["status"] = "error";
            jsonDoc["message"] = "Pointeur invalide.";
            break;
        case Enum::ReturnValue::EMPTY_QUEUE :
            jsonDoc["type"] = "response";
            jsonDoc["status"] = "error";
            jsonDoc["message"] = "File vide.";
            break;
        
        default:
            jsonDoc["type"] = "response";
            jsonDoc["status"] = "unknown";
            jsonDoc["message"] = "Commande inconnue.";
            jsonDoc["data"]["value"] = "N/A";
            break;
    }

    String jsonString;
    serializeJson(jsonDoc, jsonString);
    SerialBT.println(jsonString);
    Serial.println("Message envoyé : " + jsonString);
    return;
}

void BluetoothManager::proccessResponse(Enum::ReturnValue inReturnValue, Actions action) {
    return;
}

}
}
