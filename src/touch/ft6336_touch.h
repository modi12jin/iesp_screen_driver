#ifndef _FT6336_TOUCH_H
#define _FT6336_TOUCH_H
#include <stdio.h>

class ft6336_touch
{
public:
    ft6336_touch(int8_t sda_pin, int8_t scl_pin, int8_t rst_pin = -1, int8_t int_pin = -1);

    void begin();
    bool getTouch(uint16_t *x, uint16_t *y);
    void set_rotation(uint8_t r);

private:
    int8_t _sda, _scl, _rst, _int;
};

#endif