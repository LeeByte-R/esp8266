#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/hw_timer.h"

void hw_timer_callback(void *arg)
{
    static int state = 0;

    gpio_set_level(GPIO_NUM_12, (state ++) % 2);
}

void app_main(void)
{
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_Pin_12;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    //Initialize hw_timer for callback
    hw_timer_init(hw_timer_callback, NULL);

    //Set hw_timer timing time 1000ms with reload
    hw_timer_alarm_us(1000000, true);
}
