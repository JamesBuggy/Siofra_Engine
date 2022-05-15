#pragma once

#include <vector>
#include <cstdint>

using KeyboardState = std::vector<bool>;
using MouseButtonState = std::vector<bool>;

struct MouseState
{
    MouseButtonState buttonState{ };
    std::int32_t x{ };
    std::int32_t y{ };
};
