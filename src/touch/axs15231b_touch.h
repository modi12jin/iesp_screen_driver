#ifndef _AXS15231B_TOUCH_H
#define _AXS15231B_TOUCH_H
#include <stdio.h>
class axs15231b_touch
{
public:
    axs15231b_touch(int8_t sda_pin, int8_t scl_pin, int8_t rst_pin = -1, int8_t int_pin = -1);

    void begin();
    bool getTouch(uint16_t *x, uint16_t *y);

private:
    int8_t _sda, _scl, _rst, _int;
};
#endif
