#pragma once

#include "platform/clock.hpp"

namespace siofraEngine::core
{
    class Clock
    {
        public:
            Clock();

            void update();

            float getElapsedTime() const noexcept;

        private:
            float startTime{ };
            float elapsedTime{ };
    };
}
