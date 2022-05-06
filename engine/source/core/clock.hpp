#pragma once

#include <memory>
#include "platform/iplatformClock.hpp"

namespace siofraEngine::core
{
    class Clock
    {
        public:
            Clock(std::unique_ptr<siofraEngine::platform::IPlatformClock> platformClock);

            void update();

            float getElapsedTime() const noexcept;

        private:
            std::unique_ptr<siofraEngine::platform::IPlatformClock> platformClock{ };
            float startTime{ };
            float elapsedTime{ };
    };
}
