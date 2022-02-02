#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

static void gpio_isr_handler(void *arg)
{
    gpio_set_level(GPIO_NUM_4, 1);
}

void app_main(void)
{
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set
    io_conf.pin_bit_mask = GPIO_Pin_4;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    //interrupt of falling edge
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    //bit mask of the pins
    io_conf.pin_bit_mask = GPIO_Pin_5;
    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    //install gpio isr service
    gpio_install_isr_service(0);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(GPIO_NUM_5, gpio_isr_handler, (void *) NULL);
    
    while (1) {
        gpio_set_level(GPIO_NUM_4, 0);
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}


