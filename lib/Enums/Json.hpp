#include <string>

enum class Type {
    UNKNOWN,
    COMMAND,
    QUERY,

    END
};

enum class Actions {
    UNKNOWN,
    SET_ALTITUDE,
    DIRECTION,
    SET_VERSION,
    STOP_SOUND,
    RUN_SOUND,
    SET_DEVICE_NAME,
    GET_DEVICE_NAME,
    GET_VERSION,
    GET_ALTITUDE,
    GET_BATTERY_PERCENTAGE,


    END
};

inline Actions actionsFromString ( const std::string &inAction )
{
    if (inAction == "set_altitude")
        return Actions::SET_ALTITUDE;
    
    else if (inAction == "direction")
        return Actions::DIRECTION;
    else if (inAction == "get_battery")
        return Actions::GET_BATTERY_PERCENTAGE;
    else if (inAction == "get_altitude")
        return Actions::GET_ALTITUDE;
    else if (inAction == "set_version")
        return Actions::SET_VERSION;
    else if (inAction == "stop_sound")
        return Actions::STOP_SOUND;
    else if (inAction == "run_sound")
        return Actions::RUN_SOUND;
    else if (inAction == "set_device_name")
        return Actions::SET_DEVICE_NAME;
    else if (inAction == "get_device_name")
        return Actions::GET_DEVICE_NAME;
    else if (inAction == "get_version")
        return Actions::GET_VERSION;
    
    else
        // We need to return a value
        return Actions::UNKNOWN;
}

inline Type typeFromString ( const std::string &inType )
{
    if (inType == "command")
        return Type::COMMAND;
    else if (inType == "query")
        return Type::QUERY;
    else
        // We need to return a value
        return Type::UNKNOWN;
}