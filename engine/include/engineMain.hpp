#include <iostream>
#include <core/logging.hpp>
#include <core/assertions.hpp>
#include <core/application.hpp>

bool createGame();

int main()
{
    if(createGame())
    {
        SE_LOG_INFO("Game created");
    }

    engine::core::Application application;
    
    application.execute();
}