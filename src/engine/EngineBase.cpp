#include "EngineBase.h"

EngineBase::EngineBase(std::uint8_t size) : 
    isInitialized(false),
    isRunning(false),
    thread(),
    eventQueue(size)
{
}
  
EngineBase::~EngineBase()
{
    isRunning = false;

    if (thread.joinable())
    {
        thread.join();
    }
}

void EngineBase::start()
{
    if (isRunning || isInitialized)
    {
        throw std::runtime_error("starting an already started/initialized engine!");
    }
    else
    {
        isInitialized = true;
        isRunning = true;
        thread = std::thread(&EngineBase::doStart, this); // move assignment
    }
}

void EngineBase::doStart()
{
    while(isRunning)
    {
        std::shared_ptr<Event> e = eventQueue.dequeueHead();
        bool isProcessed = processEvent(e);
        if (!isProcessed)
        {
            processEventDerived(std::move(e));
        }
    }
}

void EngineBase::waitForTerminate()
{
    thread.join();
}

bool EngineBase::tryEnqueue(std::shared_ptr<Event> e)
{
    return eventQueue.tryEnqueue(std::move(e));
}

void EngineBase::forceEnqueue(std::shared_ptr<Event> e)
{
    eventQueue.forceEnqueueTail(std::move(e));
}

void EngineBase::priorityForceEnqueue(std::shared_ptr<Event> e)
{
    eventQueue.forceEnqueueHead(std::move(e));
}

bool EngineBase::processEvent(const std::shared_ptr<Event>& e)
{
    switch (e.get()->getEventType())
    {
        case EventType::TERMINATE:
        {
            doStop();                
            return true;
        }
        default:
        { 
            return false;
        }
    }
}

void EngineBase::doStop()
{
    isRunning = false;
}