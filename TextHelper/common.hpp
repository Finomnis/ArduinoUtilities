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

            void getTextDimensions(const char *text,
                                   uint16_t *width,
                                   uint16_t *height = nullptr);

            void setCursor(const char *text,
                           int pos_x, int pos_y,
                           HorizontalAlign align_h, VerticalAlign align_v,
                           int *rendered_width = nullptr,
                           int *rendered_height = nullptr);
            void drawText(const char *text,
                          int pos_x, int pos_y,
                          HorizontalAlign align_h, VerticalAlign align_v,
                          int *rendered_width = nullptr,
                          int *rendered_height = nullptr);
        };

        template <typename T>
        class TextWritingDisplayImpl : public TextWritingDisplay
        {
        private:
            // THIS CLASS IS NOT INSTANTIATABLE.
            // If an error happens here, it means the desired display driver
            // is not supported by the TextHelper.
            // Please provide a suitable implementation.
            // For examples, look at U8g2.hpp or Adafruit_SSD1306.hpp
            TextWritingDisplayImpl(T &) = delete;
        };
    };

    template <typename T>
    void getTextDimensions(T &display,
                           const char *text,
                           uint16_t *width,
                           uint16_t *height = nullptr)
    {
        impl::TextWritingDisplayImpl<T>(display).getTextDimensions(text, width, height);
    }

    template <typename T>
    void setCursor(T &display,
                   const char *text,
                   int pos_x, int pos_y,
                   HorizontalAlign align_h, VerticalAlign align_v,
                   int *rendered_width = nullptr,
                   int *rendered_height = nullptr)
    {
        impl::TextWritingDisplayImpl<T>(display).setCursor(text, pos_x, pos_y, align_h, align_v, rendered_width, rendered_height);
    }

    template <typename T>
    void drawText(T &display,
                  const char *text,
                  int pos_x, int pos_y,
                  HorizontalAlign align_h, VerticalAlign align_v,
                  int *rendered_width = nullptr,
                  int *rendered_height = nullptr)
    {
        impl::TextWritingDisplayImpl<T>(display).drawText(text, pos_x, pos_y, align_h, align_v, rendered_width, rendered_height);
    }
}
