#ifndef E_SCAPE_CLIENT_CIRCULAR_BUFFER_TPP
#define E_SCAPE_CLIENT_CIRCULAR_BUFFER_TPP

#include <atomic>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>

/*
    A Circular Buffer implementation

    Initializes the underlying array with default T (i.e. T()) and moves pointers in-and-out of those T's 
    without destroying the underlying T's themselves (i.e. their lifetime is bound to the lifetime of the owner of this buffer)
*/

// TODO: make the buffer have one 'extra' slot for emergency message, instead of overriding existing messages, as the latter could lead to subtle bugs and 
// undefined, hard to track behaviour

template <typename T>
CircularBuffer<T>::CircularBuffer(std::uint8_t capacity) : 
    capacity(capacity),
    currentSize(0),
    readIndex (0),
    writeIndex (0),
    buffer(std::unique_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[capacity]))
{
    if (capacity < MIN_SIZE)
    {
       throw std::invalid_argument("Size is too small for the buffer");
    }
    else if (capacity > MAX_SIZE)
    {
        throw std::invalid_argument("Size is too large for the buffer");
    }
}

template <typename T>
CircularBuffer<T>::~CircularBuffer()
{ 
}

template <typename T>
bool CircularBuffer<T>::tryEnqueueTail(std::shared_ptr<T>&& t)
{
    if (currentSize == capacity)
    {
        return false;
    }
    else
    {
        doEnqueue(std::move(t));

        return true;
    }
}

template <typename T>
void CircularBuffer<T>::forceEnqueueTail(std::shared_ptr<T>&& t)
{   
    if (currentSize == capacity)
    {
        buffer[writeIndex].swap(t);
    }
    else
    {
        doEnqueue(std::move(t));
    }
}

template <typename T>
void CircularBuffer<T>::forceEnqueueHead(std::shared_ptr<T>&& t)
{
    if (isEmpty())
    {
        doEnqueue(std::move(t));
    }
    else
    {
        buffer[readIndex].swap(t);  
    }
}

template <typename T>
void CircularBuffer<T>::doEnqueue(std::shared_ptr<T>&& t)
{
    buffer[writeIndex].swap(t);

    if (writeIndex == (capacity - 1))
    {
        writeIndex = 0;
    }
    else
    {
        writeIndex++; 
    }

    currentSize++; 
}

template <typename T>
std::shared_ptr<T> CircularBuffer<T>::dequeueHead()
{
    std::shared_ptr<T> t = std::move(buffer[readIndex]);

    if ((readIndex + 1) == capacity)
    {
        readIndex = 0;
    }
    else
    {
        readIndex++; 
    }

    currentSize--;

    return t;
}

template <typename T>
bool CircularBuffer<T>::isEmpty()
{
    return currentSize == 0;
}

template <typename T>
void CircularBuffer<T>::clear()
{
    while (!isEmpty())
    {
        dequeueHead();
    }
}

#endif