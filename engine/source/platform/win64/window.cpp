#ifdef SE_PLATFORM_WIN64

#include <SDL2/SDL.h>
#include "platform/window.hpp"

class engine::platform::Window::InternalWindow
{
public:
    InternalWindow(char const * title, int x, int y, int width, int height) :
        winPtr{SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_VULKAN)}
    {
        SE_ASSERT_TRUE(winPtr != NULL, "Failed to create SDL window");
    }

    ~InternalWindow()
    {
        SDL_DestroyWindow(winPtr);
    }
    
    SDL_Window* winPtr{ nullptr };
};

namespace engine::platform
{
    Window::Window(char const * title, int x, int y, int width, int height) :
        _internalWindow({std::make_unique<InternalWindow>(title, x, y, width, height)}),
        _shouldClose{false}
    {
        
    }

    Window::~Window()
    {
        
    }

    bool Window::shouldClose()
    {
        return _shouldClose;
    }

    void Window::pollEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                _shouldClose = true;
            }
        }
    }
}

#endif
