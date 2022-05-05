#ifdef SE_PLATFORM_WIN64

#include <SDL2/SDL.h>
#include "platform/window.hpp"

class siofraEngine::platform::Window::InternalWindow
{
public:
    InternalWindow(std::string title, int x, int y, int width, int height) :
        winPtr{SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_VULKAN)}
    {
        SE_ASSERT_TRUE(winPtr != NULL, "Failed to create SDL window");
    }

    ~InternalWindow()
    {
        SDL_DestroyWindow(winPtr);
    }
    
    SDL_Window* winPtr{ nullptr };
};

namespace siofraEngine::platform
{
    Window::Window(std::string title, int x, int y, int width, int height) :
        _internalWindow({std::make_unique<InternalWindow>(title, x, y, width, height)})
    {
        
    }

    Window::~Window()
    {
        
    }
}

#endif
