# ArduinoUtilities

Utility functions that simplify microcontroller projects based on the Arduino framework

-   `Button.hpp`:
    -   Software-debounced interrupt-based button press handling
-   `NoMoveNoCopy.hpp`
    -   Abstract base class that makes a class non-copyable and non-movable
-   `TimeHelpers.hpp`
    -   Provides functionality to check whether a timepoint lies in the past.
    -   Background: this function is millis()-overflow safe (opposed to widespread `timestamp < millis()`)
-   `ValueWatcher.hpp`
    -   Provides a Single-Producer-Multiple-Consumer (SPMC) style pipe
    -   `Value<>` class: Can hold a value
    -   `ValueWatcher<>` class: Can watch the Value<> object
    -   Whenever the `Value<>` changes, all attached `ValueWatcher<>`s get notified
    -   Intended to provide a means of abstracting data connections in your project
    -   Usually, `Value<>` is directly connected to a class that reads continuous values from a sensor
    -   `ValueWatcher<>` is then used by e.g. a Display or MQTT connection to display/publish that value
-   `TextHelper`
    -   Provides utility functions for Text Positioning on Displays
    -   Supports U8g2 and Adafruit GFX
    -   Easily extendable for new libraries
