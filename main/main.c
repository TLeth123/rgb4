#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_timer.h"
#include "esp_system.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"
#include "lv_demos.h"
#include "lvgl_init.h"
#include "i2c_lcd.h"
#include "../components/lvgl__lvgl/demos/benchmark/lv_demo_benchmark.h"
#include "../components/lvgl__lvgl/demos/widgets/lv_demo_widgets.h"

static const char *TAG = "app_main";

void lvgl_driver_init() // 初始化液晶驱动
{
    ESP_ERROR_CHECK(i2c_master_init());
    lv_init();
    lvgl_disp_init();
    lvgl_touch();
    lv_port_tick_init();
}

void lv_tick_task(void *arg) // LVGL 时钟任务
{
    while (1)
    {
        vTaskDelay((10) / portTICK_PERIOD_MS);
        lv_task_handler();
    }
}

void app_main(void)
{
    lvgl_driver_init(); // 初始化液晶驱动
    // lv_demo_music();// lvgl音乐播放例程
    lv_demo_widgets();
    // lv_demo_benchmark();

    xTaskCreate(lv_tick_task, "lv_tick_task", 4096, NULL, 1, NULL);
}
