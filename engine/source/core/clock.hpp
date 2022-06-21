#pragma once

#include <memory>
#include "platform/iplatformClock.hpp"

namespace siofraEngine::core
{
    /**
     * @brief Application clock. Maintains the applications start and elapsed time
     */
    class Clock
    {
        public:
            /**
             * @brief Clock constructor
             * 
             * @param platformClock Access to platform specific clock logic
             */
            Clock(std::unique_ptr<siofraEngine::platform::IPlatformClock> platformClock);

            /**
             * @brief Updates the application elapsed time
             */
            void update();

            /**
             * @brief Get applications elapsed time
             * 
             * @returns Elapsed application time in seconds
             */
            float getElapsedTime() const noexcept;

            /**
             * @brief Wait a specified number of milliseconds before returning
             *
             * @param ms Time to wait in milliseconds
             */
            void sleep(std::uint32_t ms) const;

        private:
            /**
             * @brief Access to platform specific clock logic
             */
            std::unique_ptr<siofraEngine::platform::IPlatformClock> platformClock{ };

            /**
             * @brief Application start time
             */
            float startTime{ };

            /**
             * @brief Application elapsed time
             */
            float elapsedTime{ };
    };
}
