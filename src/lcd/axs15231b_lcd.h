#ifndef _AXS15231B_LCD_H
#define _AXS15231B_LCD_H
#include <stdio.h>

class axs15231b_lcd
{
public:
    axs15231b_lcd(int8_t qspi_cs, int8_t qspi_clk, int8_t qspi_0,
                  int8_t qspi_1, int8_t qspi_2, int8_t qspi_3, int8_t lcd_rst);

    void begin();
    void lcd_draw_bitmap(uint16_t x_start, uint16_t y_start,
                         uint16_t x_end, uint16_t y_end, uint16_t *color_data);

private:
    int8_t _qspi_cs, _qspi_clk, _qspi_0, _qspi_1, _qspi_2, _qspi_3, _lcd_rst;
};
#endif