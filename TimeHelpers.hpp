#pragma once

#include <Arduino.h>

inline bool event_is_over(uint32_t event_time, uint32_t now)
{
    static_assert(sizeof(decltype(millis())) == sizeof(uint32_t),
                  "millis() does not return a 32-bit value! This breaks the function event_is_over().");

    int32_t diff = int32_t(now - event_time);
    return diff >= 0;
}

inline bool event_is_over(uint32_t event_time)
{
    static_assert(sizeof(decltype(millis())) == sizeof(uint32_t),
                  "millis() does not return a 32-bit value! This breaks the function event_is_over().");

    return event_is_over(event_time, millis());
}
