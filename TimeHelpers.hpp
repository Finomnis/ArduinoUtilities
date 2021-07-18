#pragma once

#include <Arduino.h>

inline bool event_is_over(uint32_t event_time, uint32_t now)
{
    int32_t diff = int32_t(now - event_time);
    return diff >= 0;
}

inline bool event_is_over(uint32_t event_time)
{
    return event_is_over(event_time, millis());
}
