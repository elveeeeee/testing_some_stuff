#ifndef E_SCAPE_CLIENT_AUDIO_ENGINE
#define E_SCAPE_CLIENT_AUDIO_ENGINE

#include <cstdint>
#include <memory>

#include "EngineBase.h"

class AudioEngine final : public EngineBase
{
    public:
        AudioEngine(std::uint8_t);
        virtual ~AudioEngine();
        
    private:
        virtual bool processEventDerived(std::shared_ptr<Event>&&);
};

#endif