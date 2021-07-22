#pragma once

#define dbg(VAL)             \
    do                       \
    {                        \
        Serial.print(#VAL);  \
        Serial.print(" = "); \
        Serial.println(VAL); \
    } while (0)
