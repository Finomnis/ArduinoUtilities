#include "common.hpp"

namespace TextHelper
{
    int getLeft(int pos_x, int width, HorizontalAlign align_h)
    {
        switch (align_h)
        {
        case HorizontalAlign::H_LEFT:
            return pos_x;
        case HorizontalAlign::H_CENTER:
            return pos_x - width / 2;
        case HorizontalAlign::H_RIGHT:
            return pos_x - width + 1;
        default:
            return 0;
        }
    }

    int getTop(int pos_y, int height, VerticalAlign align_v)
    {
        switch (align_v)
        {
        case VerticalAlign::V_TOP:
            return pos_y;
        case VerticalAlign::V_CENTER:
            return pos_y - height / 2;
        case VerticalAlign::V_BOTTOM:
            return pos_y - height + 1;
        default:
            return 0;
        }
    }

    namespace impl
    {

        void getTextDimensions(TextWritingDisplay &display,
                               const char *text,
                               uint16_t *width,
                               uint16_t *height)
        {
            if (height == nullptr)
            {
                int16_t start_x, start_y;
                uint16_t dummy_height;
                display.getTextBounds(text, &start_x, &start_y, width, &dummy_height);
            }
            else
            {
                int16_t start_x, start_y;
                display.getTextBounds(text, &start_x, &start_y, width, height);
            }
        }

        void setCursor(TextWritingDisplay &display,
                       const char *text,
                       int pos_x, int pos_y,
                       HorizontalAlign align_h, VerticalAlign align_v,
                       int *rendered_width, int *rendered_height)
        {
            int16_t start_x, start_y;
            uint16_t width, height;
            display.getTextBounds(text, &start_x, &start_y, &width, &height);

            int absolute_top = getTop(pos_y, height, align_v);
            int absolute_left = getLeft(pos_x, width, align_h);

            int cursor_x = absolute_left - start_x;
            int cursor_y = absolute_top - start_y;

            display.setCursor(cursor_x, cursor_y);

            if (rendered_height != nullptr)
                *rendered_height = height;
            if (rendered_width != nullptr)
                *rendered_width = width;
        }

        void drawText(TextWritingDisplay &display,
                      const char *text,
                      int pos_x, int pos_y,
                      HorizontalAlign align_h, VerticalAlign align_v,
                      int *rendered_width, int *rendered_height)
        {
            setCursor(display, text, pos_x, pos_y, align_h, align_v,
                      rendered_width, rendered_height);
            display.print(text);
        }
    }
}
