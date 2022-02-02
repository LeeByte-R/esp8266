#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void app_main(void)
{
    gpio_config_t io_conf;
    
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //bit mask of the pins, use GPIO4 here
    io_conf.pin_bit_mask = GPIO_Pin_4;
    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    while (1) {
        printf("%d\r\n", gpio_get_level(GPIO_NUM_4));
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

