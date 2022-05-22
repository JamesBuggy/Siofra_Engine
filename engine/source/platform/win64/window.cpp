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
    InternalWindow(std::string title, std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height, WindowFlags flags) :
        winPtr{SDL_CreateWindow(title.c_str(), x, y, width, height, mapFlags(flags))}
    {
        SE_ASSERT_TRUE(winPtr != NULL, "Failed to create SDL window");
    }

    Uint32 mapFlags(WindowFlags flags)
    {
        Uint32 sdlFlags = 0;

        if((flags & WindowFlags::WINDOW_VULKAN) == WindowFlags::WINDOW_VULKAN)
        {
            sdlFlags |= SDL_WINDOW_VULKAN;
        }

        return sdlFlags;
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
    Window::Window(std::string title, std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height, WindowFlags flags) :
        _internalWindow({std::make_unique<InternalWindow>(title, x, y, width, height, flags)}),
        flags{flags}
    {
        SE_LOG_INFO("Initialized Window");
    }

    Window::~Window()
    {
        
    }

    WindowFlags Window::getFlags()
    {
        return flags;
    }
}

#endif
