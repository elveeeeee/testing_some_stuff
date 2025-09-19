#ifndef E_SCAPE_CLIENT_WINDOWS_CONTAINER_OPENGL
#define E_SCAPE_CLIENT_WINDOWS_CONTAINER_OPENGL

#include <windows.h>
#include <GL/gl.h>
#include <GL/wglext.h>

#include "WindowsOpenGLResult.h"

class WindowsContainerOpenGL final
{
    public:
        WindowsContainerOpenGL(HINSTANCE);
        ~WindowsContainerOpenGL();

        WindowsOpenGLResult initialize();
        void showWindow(int);
        void runMessageLoop();

    private:
        using WglChoosePixelFormatARB = BOOL (WINAPI *) (HDC, const int*, const FLOAT*, UINT, int*, UINT*);
        WglChoosePixelFormatARB wglChoosePixelFormatARB = nullptr;

        using WglCreateContextAttribsARB =  HGLRC (WINAPI *) (HDC, HGLRC, const int *);
        WglCreateContextAttribsARB wglCreateContextAttribsARB = nullptr;

        BOOL initializeOpenGLExtensions();

        static LRESULT CALLBACK windowProc(HWND, UINT, WPARAM, LPARAM);

        LRESULT handleMessage(UINT, WPARAM, LPARAM);

        LRESULT process_WM_CREATE(WPARAM, LPARAM);
        LRESULT process_WM_PAINT(WPARAM, LPARAM);
        LRESULT process_WM_CLOSE(WPARAM, LPARAM);
        LRESULT process_WM_DESTROY(WPARAM, LPARAM);

        HINSTANCE hInstance;
        HWND createdHWND;
};

#endif