#ifndef E_SCAPE_CLIENT_ENGINE_EVENT_BUS
#define E_SCAPE_CLIENT_ENGINE_EVENT_BUS

#include <memory>
#include <vector>
#include <unordered_map>
#include <latch>

#include "EventBusCallbacks.h"
#include "EventType.h"
#include "Events.h"
#include "../engine/EngineBase.h"

class EventBus final  
{
    public:
        EventBus(std::shared_ptr<EventBusCallbacks>, std::shared_ptr<std::latch>);
        ~EventBus();

        void waitForReady();
        void publish(std::shared_ptr<Event>);

    private:
        std::shared_ptr<EventBusCallbacks> callbacksPtr;    
        std::shared_ptr<std::latch> readyLatchPtr; // to enforce memory_ordering_seq_cst, redundant or not, sanity reasons
};

#endif