#ifndef E_SCAPE_CLIENT_EVENTS
#define E_SCAPE_CLIENT_EVENTS

#include <cstdint>

#include "EventType.h"

class Event 
{
    public:
        virtual ~Event();
        virtual EventType getEventType();
};

class EventDatabase : public Event
{
    public:
        virtual ~EventDatabase();
        virtual EventType getEventType();
        char* getSpecializedData(); // TODO: some unimplemented shit for test purposes
};

class EventNetwork : public Event
{
    public:
        virtual ~EventNetwork();
        virtual EventType getEventType();
};

class EventUserInput : public Event
{
    public:
        virtual ~EventUserInput();
        virtual EventType getEventType();
};

class EventRendering : public Event
{
    public:
        virtual ~EventRendering();
        virtual EventType getEventType();
        char* getRenderingBuffer(); // test, delete

    private:
        char* DONT_USE_ME = nullptr; // TODO: do not use!!
};

class EventState : public Event
{
    public:
        virtual ~EventState();
        virtual EventType getEventType();
};

class EventAudio : public Event
{
    public:
        virtual ~EventAudio();
        virtual EventType getEventType();
};

class EventTerminate : public Event
{
    public:
        virtual ~EventTerminate();
        virtual EventType getEventType();
};

#endif