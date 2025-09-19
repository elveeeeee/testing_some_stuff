#include <iostream>
#include <chrono>
#include <cstdint>
#include <memory>
#include <thread>
#include <utility>
#include <vector>
#include <latch>
#include <windows.h>

#include "engine/AudioEngine.h"
#include "engine/GameStateEngine.h"
#include "engine/RenderingEngineOPENGL.h"

#include "entity/EventBus.h"
#include "entity/Events.h"
#include "entity/EventType.h"

#include "platform/WindowsContainerOpenGL.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    WindowsContainerOpenGL windowsOpenGl(hInstance);
    WindowsOpenGLResult result = windowsOpenGl.initialize();
    if (result.getSuccess() == FALSE)
    {
        return 1;
    }
    
    std::shared_ptr<std::latch> readyLatch = std::make_shared<std::latch>(1);
    std::shared_ptr<EventBusCallbacks> eventBusCallbacks = std::make_shared<EventBusCallbacks>();
    std::shared_ptr<EventBus> eventBus = std::make_shared<EventBus>(eventBusCallbacks, readyLatch);

    std::shared_ptr<GameStateEngine> 
        gameStateEngine = std::make_shared<GameStateEngine>(std::uint8_t(200));

    std::shared_ptr<RenderingEngineOpenGL> 
        renderingEngineOpenGL = std::make_shared<RenderingEngineOpenGL>(std::uint8_t(200), result.getHDC(), result.getHGLRC());

    std::shared_ptr<AudioEngine> 
        audioEngine = std::make_shared<AudioEngine>(std::uint8_t(200));

    eventBusCallbacks->subscribe(EventType::TERMINATE, gameStateEngine);
    eventBusCallbacks->subscribe(EventType::TERMINATE, renderingEngineOpenGL);
    eventBusCallbacks->subscribe(EventType::TERMINATE, audioEngine);

    eventBusCallbacks->subscribe(EventType::STATE, renderingEngineOpenGL);

    gameStateEngine->start();
    renderingEngineOpenGL->start();
    audioEngine->start();

    windowsOpenGl.showWindow(nCmdShow);

    std::shared_ptr<EventState> es = std::make_shared<EventState>();
    eventBus->publish(es);
    
    windowsOpenGl.runMessageLoop();

    return 0;
}
