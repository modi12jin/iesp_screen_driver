#include "lvgl.h"
#include "demos/lv_demos.h"
#include "pins_config.h"
#include "src/lcd/axs15231b_lcd.h"
#include "src/touch/axs15231b_touch.h"

axs15231b_lcd lcd=axs15231b_lcd(TFT_QSPI_CS,TFT_QSPI_SCK,TFT_QSPI_D0,TFT_QSPI_D1,TFT_QSPI_D2,TFT_QSPI_D3,TFT_QSPI_RST);
axs15231b_touch touch = axs15231b_touch(TP_I2C_SDA, TP_I2C_SCL, TP_RST, TP_INT);

static lv_disp_draw_buf_t draw_buf;
static lv_color_t *buf;
static lv_color_t *buf1;

//显示刷新
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  const int offsetx1 = area->x1;
  const int offsetx2 = area->x2;
  const int offsety1 = area->y1;
  const int offsety2 = area->y2;
  lcd.lcd_draw_bitmap(offsetx1,offsety1, offsetx2 + 1, offsety2 + 1, &color_p->full);
  lv_disp_flush_ready(disp);  //告诉lvgl刷新完成
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  bool touched;
  uint16_t touchX, touchY;

  touched = touch.getTouch(&touchX, &touchY);

  if (!touched) {
    data->state = LV_INDEV_STATE_REL;
  } else {
    data->state = LV_INDEV_STATE_PR;

    // 设置坐标
    data->point.x = touchX;
    data->point.y = touchY;
  }
}

void setup() {
  static lv_disp_drv_t disp_drv;

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  lcd.begin();
  touch.begin();

  lv_init();
  size_t buffer_size = sizeof(lv_color_t) * LCD_H_RES * LCD_V_RES;
  buf = (lv_color_t *)heap_caps_malloc(buffer_size, MALLOC_CAP_SPIRAM);
  buf1 = (lv_color_t *)heap_caps_malloc(buffer_size, MALLOC_CAP_SPIRAM);

  lv_disp_draw_buf_init(&draw_buf, buf, buf1, buffer_size);
  /*Initialize the display*/
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = LCD_H_RES;
  disp_drv.ver_res = LCD_V_RES;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  //disp_drv.user_data = panel_handle;
  disp_drv.full_refresh = 1;  // full_refresh 必须为 1
  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

    lv_demo_widgets(); /* 小部件示例 */
    // lv_demo_music();        /* 类似智能手机的现代音乐播放器演示 */
    // lv_demo_stress();       /* LVGL 压力测试 */
    // lv_demo_benchmark();    /* 用于测量 LVGL 性能或比较不同设置的演示 */
}

void loop() {
  lv_timer_handler();
  delay(5);
}
