#pragma once

#include "common.hpp"

#include <U8g2lib.h>

namespace TextHelper
{
    namespace impl
    {
        class U8G2TextWritingDisplay : public TextWritingDisplay
        {
        public:
            constexpr U8G2TextWritingDisplay(U8G2 &display) : display{display} {}
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

    inline void getTextDimensions(U8G2 &display,
                                  const char *text,
                                  uint16_t *width,
                                  uint16_t *height = nullptr)
    {
        impl::U8G2TextWritingDisplay wrapped(display);
        impl::getTextDimensions(wrapped, text, width, height);
    }

    inline void setCursor(U8G2 &display,
                          const char *text,
                          int pos_x, int pos_y,
                          HorizontalAlign align_h, VerticalAlign align_v,
                          int *rendered_width = nullptr,
                          int *rendered_height = nullptr)
    {
        impl::U8G2TextWritingDisplay wrapped(display);
        impl::setCursor(wrapped, text, pos_x, pos_y, align_h, align_v, rendered_width, rendered_height);
    }

    inline void drawText(U8G2 &display,
                         const char *text,
                         int pos_x, int pos_y,
                         HorizontalAlign align_h, VerticalAlign align_v,
                         int *rendered_width = nullptr,
                         int *rendered_height = nullptr)
    {
        impl::U8G2TextWritingDisplay wrapped(display);
        impl::drawText(wrapped, text, pos_x, pos_y, align_h, align_v, rendered_width, rendered_height);
    }
}
