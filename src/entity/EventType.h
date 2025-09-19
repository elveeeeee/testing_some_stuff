#ifndef E_SCAPE_CLIENT_EVENT_TYPE
#define E_SCAPE_CLIENT_EVENT_TYPE

#include <cstdint>

enum class EventType : std::uint8_t 
{
    TERMINATE,
    DATABASE,
    EMPTY,
    NETWORK,
    USER_INPUT,
    RENDERING,
    STATE,
    AUDIO
};

#endif