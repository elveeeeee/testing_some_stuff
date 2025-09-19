#include "Events.h"

/* Event */
Event::~Event()
{
}

EventType Event::getEventType()
{
    return EventType::EMPTY;
}

/* EventDatabase */
EventDatabase::~EventDatabase()
{
}

EventType EventDatabase::getEventType()
{
    return EventType::DATABASE;
}

char* EventDatabase::getSpecializedData()
{
    return nullptr; // TODO: test;
}

/* EventNetwork */
EventNetwork::~EventNetwork()
{
}

EventType EventNetwork::getEventType()
{
    return EventType::NETWORK;
}

/* EventUserInput */
EventUserInput::~EventUserInput()
{
}

EventType EventUserInput::getEventType()
{
    return EventType::USER_INPUT;
}

/* 
    EventRendering
 */
EventRendering::~EventRendering()
{
}

EventType EventRendering::getEventType()
{
    return EventType::RENDERING;
}

char* EventRendering::getRenderingBuffer()
{
    return DONT_USE_ME;
}

/*
    EventState
*/

EventState::~EventState()
{
}

EventType EventState::getEventType()
{
    return EventType::STATE;
}

/*
    EventAudio
*/
EventAudio::~EventAudio()
{
}

EventType EventAudio::getEventType()
{
    return EventType::AUDIO;
}

/* EventTerminate */
EventTerminate::~EventTerminate()
{
}

EventType EventTerminate::getEventType()
{
    return EventType::TERMINATE;
}