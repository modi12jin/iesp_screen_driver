#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

class backlight
{
public:
    backlight(int8_t led);

    void begin();
    void led_on();
    void led_off();

private:
    int8_t _led;
};

#ifdef __cplusplus
}
#endif