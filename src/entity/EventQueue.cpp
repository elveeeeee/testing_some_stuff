#include "EventQueue.h"

EventQueue::EventQueue(std::uint8_t size) : circularBuffer(size), mutex(), wait_for_read()
{
}

EventQueue::~EventQueue()
{
}

/*
    for std::condition_variable we MUST (as per official docs) use std::lock_guard for writers(modifiers) of data
*/
bool EventQueue::tryEnqueue(std::shared_ptr<Event>&& e)
{       
    std::lock_guard<std::mutex> lock(mutex);

    bool isEnqueued = circularBuffer.tryEnqueueTail(std::move(e));
    if(isEnqueued)
    {
        wait_for_read.notify_one();
    }
    return isEnqueued;
}

void EventQueue::forceEnqueueTail(std::shared_ptr<Event>&& e)
{
    std::lock_guard<std::mutex> lock(mutex);
    
    circularBuffer.forceEnqueueTail(std::move(e));
    wait_for_read.notify_one();
}

void EventQueue::forceEnqueueHead(std::shared_ptr<Event>&& e)
{
    std::lock_guard<std::mutex> lock(mutex);

    circularBuffer.forceEnqueueHead(std::move(e)); 
    wait_for_read.notify_one();
}

/*
    use std::unique_lock to be able to re-lock the woken up [waiting on condition to be satisfied] thread. std::lock_guard does not give us this option
*/
std::shared_ptr<Event> EventQueue::dequeueHead()
{
    std::unique_lock<std::mutex> lock(mutex);
    
    while(circularBuffer.isEmpty()) 
    {
        wait_for_read.wait(lock);
    }

    std::shared_ptr<Event> e = circularBuffer.dequeueHead();

    lock.unlock();

    return e;
}

bool EventQueue::isEmpty() 
{
    return circularBuffer.isEmpty();
}

void EventQueue::clear()
{
    circularBuffer.clear();
}