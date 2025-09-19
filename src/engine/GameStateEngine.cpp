#include "GameStateEngine.h"

GameStateEngine::GameStateEngine(std::uint8_t queueSize) : EngineBase(queueSize)
{
}

GameStateEngine::~GameStateEngine()
{
}

bool GameStateEngine::processEventDerived(std::shared_ptr<Event>&& e)
{
    bool isProcessed = true;

    switch (e.get()->getEventType())
    {
        case EventType::DATABASE:
        {
            std::shared_ptr<EventDatabase> ev = EventTypeConverter<Event, EventDatabase>::downcastEvent(std::move(e));
            if (ev.get()->getSpecializedData() == nullptr)
            {
                int debugstop = 5;
            }
            break;
        }
        case EventType::NETWORK:
        {
            std::shared_ptr<EventNetwork> ev = EventTypeConverter<Event, EventNetwork>::downcastEvent(std::move(e));
            break;
        }
        case EventType::USER_INPUT:
        {
            std::shared_ptr<EventUserInput> ev = EventTypeConverter<Event, EventUserInput>::downcastEvent(std::move(e));
            break;
        }
        default:
        {
            //throw std::runtime_error("No eventTypeId found!"); // todo: more info?
            isProcessed = false;
            break; 
        }
    }

    return isProcessed;
}