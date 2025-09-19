/*
    Engine running in its own thread

    NOTE: The engine is single-use; once terminated you need to create a new one
    (a re-start solution would require wrapping thread in its own thread-stateholder for memory management purposes,
    and to provide its own flag 'isRunning' copy on a per-wrapper basis instead of on a per-engine basis)
*/

#ifndef E_SCAPE_CLIENT_ENGINE_BASE
#define E_SCAPE_CLIENT_ENGINE_BASE

#include <atomic>
#include <cstdint>
#include <stdexcept>
#include <thread>

#include "../entity/EventQueue.h"
#include "../entity/Events.h"
#include "../entity/EventTypeConverter.h"

class EngineBase 
{
    public:
        explicit EngineBase(std::uint8_t);
        virtual ~EngineBase();

        virtual void start() final;
        void waitForTerminate();

        bool tryEnqueue(std::shared_ptr<Event>);
        void forceEnqueue(std::shared_ptr<Event>);
        void priorityForceEnqueue(std::shared_ptr<Event>);

    protected:
        virtual void doStart();
        virtual void doStop();

        virtual bool processEvent(const std::shared_ptr<Event>&) final;
        virtual bool processEventDerived(std::shared_ptr<Event>&&) = 0;

        EventQueue eventQueue;

        std::atomic<bool> isInitialized;
        std::atomic<bool> isRunning;
    private:
        std::thread thread;
};
  
#endif