#include <Arduino.h>

backlight::backlight(int8_t led)
{
    _led = led;
}

void backlight::begin()
{
  pinMode(_led, OUTPUT);
}

void backlight::led_on()
{
  digitalWrite(_led, 1);
}

void backlight::led_off()
{
  digitalWrite(_led, 0);
}