#include "EventBusCallbacks.h"

EventBusCallbacks::EventBusCallbacks() : callbacks()
{
}

void EventBusCallbacks::subscribe(EventType eventType, std::shared_ptr<EngineBase> enginePtr)
{
    /*
        this: 
    
        std::vector<std::shared_ptr<EngineBase>> underlyingVec = callbacks2.find(eventType)->second;
        callbacks2.find(eventType)->second.push_back(enginePtr);

        has caused a copy of the underlying vector in the map to be made due to copy-on-assignment

        changing to reference, i.e. :

        std::vector<std::shared_ptr<EngineBase>>& underlyingVec = callbacks2.find(eventType)->second;

        fixed it, but theres no reason to do that [anymore]
    */

    callbacks.try_emplace(eventType);
    callbacks.find(eventType)->second.push_back(enginePtr);
}

const std::vector<std::shared_ptr<EngineBase>>& EventBusCallbacks::getCallbacks(EventType eventType) const
{
    return callbacks.find(eventType)->second;
}
