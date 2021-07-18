#pragma once

#include "../utils/TimeHelpers.hpp"

#include <Arduino.h>

template <uint32_t PIN>
class Button
{
private:
    static constexpr uint32_t DEBOUNCE_TIME_MS = 100;
    static constexpr uint32_t LONG_PRESS_DELAY_MS = 500;
    static constexpr uint32_t LONG_PRESS_RATE_MS = 200;

public:
    void init()
    {
        pinMode(PIN, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(PIN),
                        Button<PIN>::on_button_change, CHANGE);
    }

    bool was_triggered()
    {
        // Take value and clear
        noInterrupts();
        bool result = pressed;
        pressed = false;
        interrupts();

        return result;
    }

    bool was_longpressed()
    {
        bool result = false;

        noInterrupts();
        if (button_state_pressed)
        {
            uint32_t now = millis();
            uint32_t duration = now - last_button_change;
            if (duration >= LONG_PRESS_DELAY_MS + num_longpress_fired * LONG_PRESS_RATE_MS)
            {
                num_longpress_fired++;
                result = true;
            }
        }
        interrupts();

        return result;
    }

    static Button &get()
    {
        static Button button{};
        return button;
    };

private:
    static void
    on_button_change()
    {
        if (digitalRead(PIN) == LOW)
        {
            get().on_press();
        }
        else
        {
            get().on_release();
        }
    }

    void on_press()
    {
        uint32_t now = millis();

        // Update debounce end
        uint32_t previous_debounce_end = debounce_end;
        debounce_end = now + DEBOUNCE_TIME_MS;

        // Update button pressed state
        bool button_was_pressed = button_state_pressed;
        button_state_pressed = true;

        // If already pressed, do nothing
        if (button_was_pressed)
        {
            return;
        }

        // Update button duration timer
        last_button_change = now;
        num_longpress_fired = 0;

        // If we are still in the debounce period, do nothing
        if (!event_is_over(previous_debounce_end, now))
        {
            return;
        }

        // Register 'press' event
        pressed = true;
    }

    void
    on_release()
    {
        uint32_t now = millis();
        debounce_end = now + DEBOUNCE_TIME_MS;

        // Update button press state
        bool button_was_pressed = button_state_pressed;
        button_state_pressed = false;

        if (!button_was_pressed)
        {
            return;
        }

        // Update button duration timer
        last_button_change = now;
    }

private:
    bool pressed = false;
    bool button_state_pressed = false;
    uint32_t last_button_change = 0;
    uint32_t debounce_end = 0;
    uint32_t num_longpress_fired = 0;
};
