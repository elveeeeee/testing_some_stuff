#include "WindowsContainerOpenGL.h"

WindowsContainerOpenGL::WindowsContainerOpenGL(HINSTANCE hInstance) : 
    hInstance(hInstance)
{
}

WindowsContainerOpenGL::~WindowsContainerOpenGL()
{
}

BOOL WindowsContainerOpenGL::initializeOpenGLExtensions()
{
    const wchar_t CLASS_NAME[] = L"Init_Windows_OpenGL";

    WNDCLASSEX window_class = { };

    window_class.cbSize = sizeof(window_class);
    window_class.lpfnWndProc   = DefWindowProc;
    window_class.hInstance     = hInstance;
    window_class.lpszClassName = CLASS_NAME;
    window_class.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    
    if (RegisterClassEx(&window_class) == FALSE)
    {
        return FALSE;
    }

    HWND hwnd = CreateWindowEx(
        0,                      
        CLASS_NAME,             
        CLASS_NAME,  
        WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,         
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        hInstance,  
        NULL);

    if (hwnd == NULL)
    {
        return FALSE;
    }

    HDC hdc = GetDC(hwnd);
    if (hdc == NULL)
    {
        return FALSE;
    }

    PIXELFORMATDESCRIPTOR tempPFD = {0} ;
    tempPFD.nSize = sizeof(tempPFD);
    tempPFD.nVersion = 1;
    tempPFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    tempPFD.iPixelType = PFD_TYPE_RGBA;
    tempPFD.cColorBits = 32;
    tempPFD.cAlphaBits = 8;
    tempPFD.cDepthBits = 24;
    
    int tempPFDID = ChoosePixelFormat(hdc, &tempPFD);
    if (tempPFDID == 0)
    {
        return FALSE;
    }

    SetPixelFormat(hdc, tempPFDID, &tempPFD);

    HGLRC hglrc = wglCreateContext(hdc);
    if (hglrc == NULL) 
    {
        return FALSE;
    }

    if (wglMakeCurrent(hdc, hglrc) == FALSE) 
    {
        return FALSE;
    }

    wglChoosePixelFormatARB = (WglChoosePixelFormatARB)(wglGetProcAddress("wglChoosePixelFormatARB"));
    if (wglChoosePixelFormatARB == nullptr) 
    {
        return FALSE;
    }

    wglCreateContextAttribsARB = (WglCreateContextAttribsARB) ((wglGetProcAddress("wglCreateContextAttribsARB")));
    if (wglCreateContextAttribsARB == nullptr) 
    {
        return FALSE;
    }

    wglMakeCurrent(hdc, NULL);
    wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);

    return TRUE;
}

WindowsOpenGLResult WindowsContainerOpenGL::initialize()
{   
    WindowsOpenGLResult result(FALSE);

    BOOL extensionsAvailable = initializeOpenGLExtensions();
    if (!extensionsAvailable)
    {
        return result;
    }

    const wchar_t CLASS_NAME[]  = L"E_Scape_Client_Windows_OpenGL";

    WNDCLASSEX wcex = {0};     
    wcex.cbSize = sizeof(wcex);
    wcex.lpfnWndProc   = windowProc;
    wcex.hInstance     = hInstance;
    wcex.lpszClassName = CLASS_NAME;
    wcex.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (RegisterClassEx(&wcex) == FALSE)
    {
        return result;
    }

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Windows_OpenGL",
        WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance, 
        /*
            Passing 'this' pointer so that the WM_NCCREATE can read this class (windowProc is static!)
        */
        this);

    HDC hdc = GetDC(hwnd);

    const int pixelAttribs[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_ALPHA_BITS_ARB, 8,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
        WGL_SAMPLES_ARB, 4,
        0 // end of list
    };

    int pixelFormatID; 
    UINT numFormats;

    BOOL status = wglChoosePixelFormatARB(hdc, pixelAttribs, NULL, 1, &pixelFormatID, &numFormats);
    if (status == FALSE || numFormats == 0)
    {
        return result;
    }

    PIXELFORMATDESCRIPTOR PFD;
    DescribePixelFormat(hdc, pixelFormatID, sizeof(PFD), &PFD);
    SetPixelFormat(hdc, pixelFormatID, &PFD);

    const int major_min = 3;
    const int minor_min = 3;
    int  contextAttribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
        WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0 // signalling end of the list
    };
    HGLRC hglrc = wglCreateContextAttribsARB(hdc, 0, contextAttribs);
    if (hglrc == NULL) 
    {
        return result;
    }

    result.setSuccess(TRUE);
    result.setHDC(hdc);
    result.setHGLRC(hglrc);

    return result;
}

void WindowsContainerOpenGL::showWindow(int nCmdShow)
{
    ShowWindow(createdHWND, nCmdShow);
}

/*
    Static(windowProc)-to-member function so called 'cast' using SetWindowLongPtr and GetWindowLongPtr
 */
LRESULT CALLBACK WindowsContainerOpenGL::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WindowsContainerOpenGL* pThis = nullptr;

    if (uMsg == WM_NCCREATE)
    {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (WindowsContainerOpenGL*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
        /*
            the HWND has to be cached from this message, as WM_NCCREATE is the 'first' message received with complete HWND
            and the CreateWindowsEx does not return after a bunch of messages have been pumped already.

            otherwise we would be using an un-initialized HWND reference for processing messages!
        */
        pThis->createdHWND = hwnd;

        return TRUE;
    }
    else
    {
        pThis = (WindowsContainerOpenGL*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (pThis)
    {
        return pThis->handleMessage(uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

LRESULT WindowsContainerOpenGL::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {   
        case WM_CREATE:
        {
            return process_WM_CREATE(wParam, lParam);
        }
        case WM_PAINT:
        {
            return process_WM_PAINT(wParam, lParam);
        } 
        case WM_CLOSE:
        {
            return process_WM_CLOSE(wParam, lParam);
        }
        case WM_DESTROY:
        {
            return process_WM_DESTROY(wParam, lParam);
        }
        default:
        {
            return DefWindowProc(createdHWND, uMsg, wParam, lParam);
        }
    }
}

/*
    make sure this is always called from the same thread that initialized HWND
*/
void WindowsContainerOpenGL::runMessageLoop()
{
    MSG msg;
    BOOL bRet;

    while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    { 
        if (bRet == -1)
        {
            // handle the error and possibly exit
        }
        else
        {
            TranslateMessage(&msg); 
            DispatchMessage(&msg); 
        }
    }
}

LRESULT WindowsContainerOpenGL::process_WM_PAINT(WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    BeginPaint(createdHWND, &ps);
    EndPaint(createdHWND, &ps);

    return 0;
}

LRESULT WindowsContainerOpenGL::process_WM_CREATE(WPARAM wParam, LPARAM lParam)
{
    return 0;
}

LRESULT WindowsContainerOpenGL::process_WM_CLOSE(WPARAM wParam, LPARAM lParam)
{
    DestroyWindow(createdHWND);
    return 0;
}

LRESULT WindowsContainerOpenGL::process_WM_DESTROY(WPARAM wParam, LPARAM lParam)
{
    PostQuitMessage(0);
    return 0;
}