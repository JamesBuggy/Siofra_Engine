#include <iostream>
#include <core/logging.hpp>
#include <core/assertions.hpp>
#include <platform/platform.hpp>
#include <platform/window.hpp>

int main()
{
    engine::platform::initialize();
    auto window = engine::platform::Window("Test", 100, 100, 800, 600);

    SE_LOG_TRACE("Trace log");
    SE_LOG_DEBUG("Debug log");
    SE_LOG_INFO("Info log");
    //SE_ASSERT_TRUE(false, "Some assert message");
    SE_LOG_WARNING("Warning log");
    SE_LOG_ERROR("Error log");
    SE_LOG_CRITICAL("Critical log");

    while(true)
    {
        window.pollEvents();
        if(window.shouldClose())
        {
            break;
        }
    }

    engine::platform::cleanUp();
}
