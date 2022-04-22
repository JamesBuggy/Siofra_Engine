#ifdef SE_PLATFORM_WINDOWS

#include <SDL2/SDL.h>
#include "platform/window.hpp"

struct engine::platform::Window::WindowState
{
    SDL_Window* winPtr{ nullptr };

    WindowState(char const * title, int x, int y, int width, int height) :
        winPtr{SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_VULKAN)}
    {
        SE_ASSERT_TRUE(winPtr != NULL, "Failed to create SDL window");
    }

    ~WindowState()
    {
        SDL_DestroyWindow(winPtr);
    }
};

namespace engine::platform
{
    Window::Window(char const * title, int x, int y, int width, int height) :
        _windowState({std::make_unique<WindowState>(title, x, y, width, height)}),
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
