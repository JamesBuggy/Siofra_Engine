#include "core/clock.hpp"

namespace siofraEngine::core
{
    Clock::Clock(std::unique_ptr<siofraEngine::platform::IPlatformClock> platformClock) :
        platformClock{std::move(platformClock)},
        startTime{this->platformClock->getAbsoluteTime()},
        elapsedTime{0.0f}
    {

    }

    void Clock::update()
    {
        float currentTime = platformClock->getAbsoluteTime();
        elapsedTime = currentTime - startTime;
    }

    float Clock::getElapsedTime() const noexcept
    {
        return elapsedTime;
    }

    float Clock::getAbsoluteTime() const noexcept
    {
        return platformClock->getAbsoluteTime();
    }

    void Clock::sleep(std::uint32_t ms) const
    {
        platformClock->sleep(ms);
    }
}
