#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void app_main(void)
{
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO4/5
    io_conf.pin_bit_mask = GPIO_Pin_4 | GPIO_Pin_5;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    int four = 1, five = 0;

    while (1) {
        gpio_set_level(GPIO_NUM_4, four);
        gpio_set_level(GPIO_NUM_5, five);
        four = (four + 1) % 2;
        five = (five + 1) % 2;
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}