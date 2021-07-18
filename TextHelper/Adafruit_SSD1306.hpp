#pragma once

#include "common.hpp"

#include <Adafruit_SSD1306.h>

namespace TextHelper
{
    namespace impl
    {
        template <>
        class TextWritingDisplayImpl<Adafruit_SSD1306> : public TextWritingDisplay
        {
        public:
            constexpr TextWritingDisplayImpl(Adafruit_SSD1306 &display) : display{display} {}

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
                display.getTextBounds(text, 0, 0, x, y, width, height);
            }

        private:
            Adafruit_SSD1306 &display;
        };
    }
}
