#include "AudioEngine.h"

AudioEngine::AudioEngine(std::uint8_t queueSize) : EngineBase(queueSize)
{
}

AudioEngine::~AudioEngine()
{
}

bool AudioEngine::processEventDerived(std::shared_ptr<Event>&& e)
{
    bool isProcessed = true; // TODO: try 'false' as default?

    switch (e.get()->getEventType())
    {
        case EventType::AUDIO:
        {
            std::shared_ptr<EventAudio> ev = EventTypeConverter<Event, EventAudio>::downcastEvent(std::move(e));
            
            break;
        }
        default:
        {
            isProcessed = false;
            break;
        }
    }

    return isProcessed;
}   
