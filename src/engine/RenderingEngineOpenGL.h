#ifndef E_SCAPE_CLIENT_RENDERING_ENGINE_OPENGL
#define E_SCAPE_CLIENT_RENDERING_ENGINE_OPENGL

#include "EngineBase.h"
#include <windows.h>
#include "GL/gl.h"
#include "GL/glext.h"

class RenderingEngineOpenGL final : public EngineBase
{
    public:
        RenderingEngineOpenGL(std::uint8_t, HDC, HGLRC);
        virtual ~RenderingEngineOpenGL();

    private:
        bool initializeProcAddresses();
        virtual void doStart();
        virtual bool processEventDerived(std::shared_ptr<Event>&&);

        HDC hdc;
        HGLRC hglrc;

        using GlGenVertexArrays = void (WINAPI *) (GLsizei, GLuint*);
        GlGenVertexArrays glGenVertexArrays = nullptr;

        using GlBindVertexArray = void (WINAPI *) (GLuint);
        GlBindVertexArray glBindVertexArray = nullptr;

        using GlGenBuffers = void (WINAPI *) (GLsizei, GLuint*);
        GlGenBuffers glGenBuffers = nullptr;

        using GlBindBuffer = void (WINAPI *) (GLenum, GLuint);
        GlBindBuffer glBindBuffer = nullptr; 

        using GlBufferData = void (WINAPI *) (GLenum, GLsizeiptr, const void*, GLenum);
        GlBufferData glBufferData = nullptr;

        using GlEnableVertexAttribArray = void (WINAPI *) (GLuint);
        GlEnableVertexAttribArray glEnableVertexAttribArray = nullptr;

        using GlDisableVertexAttribArray = void (WINAPI *) (GLuint);
        GlDisableVertexAttribArray glDisableVertexAttribArray = nullptr;

        using GlVertexAttribPointer = void (WINAPI *) (GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
        GlVertexAttribPointer glVertexAttribPointer = nullptr;
    };

#endif