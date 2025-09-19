#ifndef E_SCAPE_CLIENT_EVENT_BUS_SUBSCRIBER
#define E_SCAPE_CLIENT_EVENT_BUS_SUBSCRIBER

#include <memory>
#include <unordered_map>
#include <vector>

#include "../engine/EngineBase.h"
#include "EventType.h"


class EventBusCallbacks final 
{
    public:
        EventBusCallbacks();
        void subscribe(EventType, std::shared_ptr<EngineBase>);
        const std::vector<std::shared_ptr<EngineBase>>& getCallbacks(EventType) const;

    private:
        std::unordered_map<EventType, std::vector<std::shared_ptr<EngineBase>>> callbacks;
};


#endif