#ifndef E_SCAPE_CLIENT_GAME_STATE_ENGINE
#define E_SCAPE_CLIENT_GAME_STATE_ENGINE

#include <cstdint>
#include <memory>

#include "EngineBase.h"

class GameStateEngine final : public EngineBase
{
    public:
        GameStateEngine(std::uint8_t);
        virtual ~GameStateEngine();

    private:
        virtual bool processEventDerived(std::shared_ptr<Event>&&);
};

#endif