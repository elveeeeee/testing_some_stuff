#include "RenderingEngineOPENGL.h"

RenderingEngineOpenGL::RenderingEngineOpenGL(std::uint8_t queueSize, HDC hdc, HGLRC hglrc)
     : EngineBase(queueSize), hdc(hdc), hglrc(hglrc)
{
}

RenderingEngineOpenGL::~RenderingEngineOpenGL()
{
}

bool RenderingEngineOpenGL::initializeProcAddresses()
{
    // all proc lookups go here
    glGenVertexArrays = (GlGenVertexArrays)(wglGetProcAddress("glGenVertexArrays"));
    if (glGenVertexArrays == nullptr) 
    {
        return false;
    }

    glBindVertexArray = (GlBindVertexArray)(wglGetProcAddress("glBindVertexArray"));
    if (glBindVertexArray == nullptr)
    {
        return false;
    }

    glGenBuffers = (GlGenBuffers)(wglGetProcAddress("glGenBuffers"));
    if (glGenBuffers == nullptr)
    {
        return false;
    }

    glBindBuffer = (GlBindBuffer)(wglGetProcAddress("glBindBuffer"));
    if (glBindBuffer == nullptr)
    {
        return false;
    }

    glBufferData = (GlBufferData)(wglGetProcAddress("glBufferData"));
    if (glBufferData == nullptr)
    {
        return false;
    }

    glEnableVertexAttribArray = (GlEnableVertexAttribArray)(wglGetProcAddress("glEnableVertexAttribArray"));
    if (glEnableVertexAttribArray == nullptr)
    {
        return false;
    }

    glDisableVertexAttribArray = (GlDisableVertexAttribArray)(wglGetProcAddress("glDisableVertexAttribArray"));
    if (glDisableVertexAttribArray == nullptr)
    {
        return false;
    }

    glVertexAttribPointer = (GlVertexAttribPointer)(wglGetProcAddress("glVertexAttribPointer"));
    if (glVertexAttribPointer == nullptr)
    {
        return false;
    }


    return true;
}


void RenderingEngineOpenGL::doStart()
{
    wglMakeCurrent(hdc, hglrc);
    if (!initializeProcAddresses())
    {
        throw std::runtime_error("cannot initialize OPENGL functions");
    }
    EngineBase::doStart();
}

bool RenderingEngineOpenGL::processEventDerived(std::shared_ptr<Event>&& e)
{
    bool isProcessed = true;

    switch (e.get()->getEventType())
    {
        case EventType::STATE:
        {
            glClearColor(0.129f, 0.586f, 0.949f, 1.0f); // rgb(33,150,243)
            glClear(GL_COLOR_BUFFER_BIT);

            GLfloat g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
            };

            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
            );

            glDrawArrays(GL_TRIANGLES, 0, 3);
            glDisableVertexAttribArray(0);

            SwapBuffers(hdc);
            
            break;
        }
        default: 
        { 
            isProcessed = false;
            break;
        }
    }

    return isProcessed;
}

