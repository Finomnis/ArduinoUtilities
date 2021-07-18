#pragma once

#include <Arduino.h>

namespace TextHelper
{
    enum VerticalAlign
    {
        V_BOTTOM,
        V_CENTER,
        V_TOP
    };
    enum HorizontalAlign
    {
        H_LEFT,
        H_CENTER,
        H_RIGHT
    };

    int getLeft(int pos_x, int width, HorizontalAlign align_h);
    int getTop(int pos_y, int height, VerticalAlign align_v);

    namespace impl
    {
        class TextWritingDisplay
        {
        public:
            virtual void setCursor(int16_t, int16_t) = 0;
            virtual void print(const char *) = 0;
            virtual void getTextBounds(const char *, int16_t *, int16_t *, uint16_t *, uint16_t *) = 0;
        };

        void getTextDimensions(TextWritingDisplay &display,
                               const char *text,
                               uint16_t *width,
                               uint16_t *height = nullptr);

        void setCursor(TextWritingDisplay &display,
                       const char *text,
                       int pos_x, int pos_y,
                       HorizontalAlign align_h, VerticalAlign align_v,
                       int *rendered_width = nullptr,
                       int *rendered_height = nullptr);
        void drawText(TextWritingDisplay &display,
                      const char *text,
                      int pos_x, int pos_y,
                      HorizontalAlign align_h, VerticalAlign align_v,
                      int *rendered_width = nullptr,
                      int *rendered_height = nullptr);
    };
}
