#ifndef E_SCAPE_CLIENT_CIRCULAR_BUFFER
#define E_SCAPE_CLIENT_CIRCULAR_BUFFER

template <typename T>
class CircularBuffer
{
    public:
        explicit CircularBuffer(std::uint8_t);
        ~CircularBuffer();

        bool tryEnqueueTail(std::shared_ptr<T>&&);
        void forceEnqueueTail(std::shared_ptr<T>&&);
        void forceEnqueueHead(std::shared_ptr<T>&&);
        std::shared_ptr<T> dequeueHead();

        bool isEmpty();
        void clear();
    private:
        void doEnqueue(std::shared_ptr<T>&&);

        std::uint8_t capacity;

        std::uint8_t readIndex;
        std::uint8_t writeIndex;

        std::uint8_t currentSize;

        std::unique_ptr<std::shared_ptr<T>[]> buffer;

        static const std::uint8_t MIN_SIZE = 1; // TODO: hardcoded
        static const std::uint8_t MAX_SIZE = 200; // TODO: hardcoded
};

#include "CircularBuffer.tpp"

#endif 
