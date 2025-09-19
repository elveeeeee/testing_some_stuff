#include "WindowsOpenGLResult.h"

WindowsOpenGLResult::WindowsOpenGLResult(BOOL success) : success(success), hdc(nullptr), hglrc(nullptr) 
{
}

WindowsOpenGLResult::~WindowsOpenGLResult()
{
}

void WindowsOpenGLResult::setSuccess(BOOL isSuccess)
{
    success = isSuccess;
}

void WindowsOpenGLResult::setHDC(HDC newHdc)
{
    hdc = newHdc;
}

void WindowsOpenGLResult::setHGLRC(HGLRC newHglrc)
{
    hglrc = newHglrc;
}

BOOL WindowsOpenGLResult::getSuccess()
{
    return success;
}

HDC WindowsOpenGLResult::getHDC()
{
    if (hdc == nullptr)
    {
        throw std::runtime_error("resulting HDC was nullptr!");
    }

    return hdc;
}

HGLRC WindowsOpenGLResult::getHGLRC()
{
    if (hglrc == nullptr)
    {
        throw std::runtime_error("resulting HGLRC was nullptr!");
    }

    return hglrc;
}
