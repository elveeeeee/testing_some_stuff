/*
    Responsible for synchronizing access to the underlying collection of events
*/

#ifndef E_SCAPE_CLIENT_EVENT_QUEUE
#define E_SCAPE_CLIENT_EVENT_QUEUE

#include <condition_variable>
#include <cstdint>
#include <memory>
#include <mutex>

#include "Events.h"
#include "CircularBuffer.h"

class EventQueue 
{
public: 
    explicit EventQueue(std::uint8_t);
    ~EventQueue();

    bool tryEnqueue(std::shared_ptr<Event>&&);
    void forceEnqueueTail(std::shared_ptr<Event>&&);
    void forceEnqueueHead(std::shared_ptr<Event>&&);
    std::shared_ptr<Event> dequeueHead();

    bool isEmpty();
    void clear();

private:
    CircularBuffer<Event> circularBuffer;

    std::mutex mutex;
    std::condition_variable wait_for_read;
    bool terminate;
};

#endif