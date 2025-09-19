cmake_minimum_required(VERSION 4.0.2)

project(E-Scape-Client VERSION 1.0) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_executable(main WIN32 src/main.cpp)
target_compile_options(main PUBLIC -municode)
target_link_options(main PUBLIC -municode)

target_link_libraries(main PUBLIC libopengl32.a)

target_sources(main PUBLIC src/engine/AudioEngine.cpp)
target_sources(main PUBLIC src/engine/EngineBase.cpp)
target_sources(main PUBLIC src/engine/GameStateEngine.cpp)
target_sources(main PUBLIC src/engine/RenderingEngineOpenGL.cpp)

target_sources(main PUBLIC src/entity/CircularBuffer.tpp)
target_sources(main PUBLIC src/entity/EventBus.cpp)
target_sources(main PUBLIC src/entity/EventBusCallbacks.cpp)
target_sources(main PUBLIC src/entity/EventQueue.cpp)
target_sources(main PUBLIC src/entity/Events.cpp)

target_sources(main PUBLIC src/platform/WindowsContainerOpenGL.cpp)
target_sources(main PUBLIC src/platform/WindowsOpenGLResult.cpp)