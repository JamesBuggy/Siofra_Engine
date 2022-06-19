#pragma once

#include "core/logging.hpp"
#include "core/serviceLocator/serviceLocator.hpp"
#include "systems/events/eventSystem.hpp"
#include "platform/platform.hpp"

namespace siofraEngine::core
{
    /**
     * @brief Application base. Base class for the application layer. Performs initializations prior to application layer creation.
     */
    class ApplicationBase
    {
    public:
        /**
         * @brief ApplicationBase constructor
         */
        ApplicationBase()
        {
            SE_LOG_INFO("Application Init");
            siofraEngine::platform::initialize();

            ServiceLocator::provide<systems::EventSystem>();
        }
        
        /**
         * @brief ApplicationBase destructor
         */ 
        virtual ~ApplicationBase()
        {
            SE_LOG_INFO("Application Shutdown");
            siofraEngine::platform::cleanUp();
        }

        /**
         * @brief Begin the application update loop
         */
        virtual void execute() = 0;
    };
}
