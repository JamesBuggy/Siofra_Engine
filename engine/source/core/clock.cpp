#include "core/clock.hpp"

namespace siofraEngine::core
{
    Clock::Clock() :
        startTime{siofraEngine::platform::Clock::getAbsoluteTime()},
        elapsedTime{0.0f}
    {

    }

    void Clock::update()
    {
        float currentTime = siofraEngine::platform::Clock::getAbsoluteTime();
        elapsedTime = currentTime - startTime;
    }

    float Clock::getElapsedTime() const noexcept
    {
        return elapsedTime;
    }
}
