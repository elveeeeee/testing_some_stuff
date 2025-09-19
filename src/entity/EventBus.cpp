#include "EventBus.h"
#include "EventBusCallbacks.h"

EventBus::EventBus(std::shared_ptr<EventBusCallbacks> callbacksPtr, std::shared_ptr<std::latch> latchPtr) : 
    callbacksPtr(std::move(callbacksPtr)), readyLatchPtr(std::move(latchPtr))
{
}

EventBus::~EventBus()
{
}

void EventBus::waitForReady()
{
    readyLatchPtr->wait();
}

void EventBus::publish(std::shared_ptr<Event> ePtr)
{   
    const std::vector<std::shared_ptr<EngineBase>>& callbacks = callbacksPtr->getCallbacks(ePtr->getEventType());

    for (const std::shared_ptr<EngineBase>& callback : callbacks)
    {
        callback->tryEnqueue(ePtr);
    }
}