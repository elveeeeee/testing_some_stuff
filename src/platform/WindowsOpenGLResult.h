#ifndef E_SCAPE_CLIENT_WINDOWS_OPEN_GL_RESULT
#define E_SCAPE_CLIENT_WINDOWS_OPEN_GL_RESULT

#include <windows.h>
#include <stdexcept>
/*
    encapsulates initialization result along with the data to be passed along,
    so that we don't have to store that on the initializers' side.
    
    those values (HDC, HGLRC) are to be consumed by another thread. We want to explicitly avoid the association
    of encapsulated data with the initializer(producer)
*/
class WindowsOpenGLResult final
{
    public:
        explicit WindowsOpenGLResult(BOOL);
        ~WindowsOpenGLResult();

        void setSuccess(BOOL);
        void setHDC(HDC);
        void setHGLRC(HGLRC);

        BOOL getSuccess();
        HDC getHDC();
        HGLRC getHGLRC();

    private:
        BOOL success;
        HDC hdc;
        HGLRC hglrc;
};


#endif
