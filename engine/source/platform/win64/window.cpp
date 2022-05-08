#ifdef SE_PLATFORM_WIN64

#include <SDL2/SDL.h>
#include "platform/window.hpp"

class siofraEngine::platform::Window::InternalWindow
{
public:
    /**
     * @brief SDL window Constructor
     * 
     * @param title Window title
     * @param x Initial window X coordinate
     * @param y Initial window Y coordinate
     * @param width Initial window width
     * @param height Initial window height
     */
    InternalWindow(std::string title, int x, int y, int width, int height) :
        winPtr{SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_VULKAN)}
    {
        SE_ASSERT_TRUE(winPtr != NULL, "Failed to create SDL window");
    }

    /**
     * @brief SDL window destructor
     */
    ~InternalWindow()
    {
        SDL_DestroyWindow(winPtr);
    }
    
    /**
     * @brief SDL window pointer
     */
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
