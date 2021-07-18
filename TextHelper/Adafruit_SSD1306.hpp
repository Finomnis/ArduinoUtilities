#pragma once

#include "common.hpp"

#include <Adafruit_SSD1306.h>

namespace TextHelper
{
    namespace impl
    {
        class Adafruit_SSD1306TextWritingDisplay : public TextWritingDisplay
        {
        public:
            constexpr Adafruit_SSD1306TextWritingDisplay(Adafruit_SSD1306 &display) : display{display} {}
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

    inline void getTextDimensions(Adafruit_SSD1306 &display,
                                  const char *text,
                                  uint16_t *width,
                                  uint16_t *height = nullptr)
    {
        impl::Adafruit_SSD1306TextWritingDisplay wrapped(display);
        impl::getTextDimensions(wrapped, text, width, height);
    }

    inline void setCursor(Adafruit_SSD1306 &display,
                          const char *text,
                          int pos_x, int pos_y,
                          HorizontalAlign align_h, VerticalAlign align_v,
                          int *rendered_width = nullptr,
                          int *rendered_height = nullptr)
    {
        impl::Adafruit_SSD1306TextWritingDisplay wrapped(display);
        impl::setCursor(wrapped, text, pos_x, pos_y, align_h, align_v, rendered_width, rendered_height);
    }

    inline void drawText(Adafruit_SSD1306 &display,
                         const char *text,
                         int pos_x, int pos_y,
                         HorizontalAlign align_h, VerticalAlign align_v,
                         int *rendered_width = nullptr,
                         int *rendered_height = nullptr)
    {
        impl::Adafruit_SSD1306TextWritingDisplay wrapped(display);
        impl::drawText(wrapped, text, pos_x, pos_y, align_h, align_v, rendered_width, rendered_height);
    }
}
