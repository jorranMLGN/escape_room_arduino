#include <Arduino.h>

#include "base/main_app.h"

namespace base
{
    main_app::main_app()
        : m_led(0),
          m_timer(1000)
    {
    }

    void main_app::init()
    {
        m_timer.start();
        Serial.begin(9600);
        Serial.println("main_app::init()");
    }

    void main_app::loop()
    {
        if (m_timer.is_triggered())
        {
            Serial.println("Timer_triggered");
            Serial.println(millis());
        }
    }
} // namespace base
