#pragma once

#include "common.hpp"

#include <U8g2lib.h>

namespace TextHelper
{
    namespace impl
    {
        template <>
        class TextWritingDisplayImpl<U8G2> : public TextWritingDisplay
        {
        public:
            constexpr TextWritingDisplayImpl(U8G2 &display) : display{display} {}

            inline void setCursor(int16_t x, int16_t y) override
            {
                display.setCursor(x, y);
            }
            inline void print(const char *text) override
            {
                display.print(text);
            }
            inline void getTextBounds(const char *text, int16_t *x, int16_t *y, uint16_t *width, uint16_t *height) override
            {
                *width = display.getStrWidth(text);
                *height = display.getAscent();
                *x = 0;
                *y = -int16_t(display.getAscent());
            }

        private:
            U8G2 &display;
        };
    }
}
