//
// Created by nikita on 03.05.24.
//

#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "lightbulb";

#define BLUE_LED 5

static void configure_internal_led(void)
{
    gpio_reset_pin(BLUE_LED);
    gpio_set_direction(BLUE_LED, GPIO_MODE_OUTPUT);
}

void internal_led_on(void)
{
    configure_internal_led();
    gpio_set_level(BLUE_LED, 0);
    ESP_LOGI(TAG, "Internal LED ON\n");
}

void internal_led_off(void)
{
    configure_internal_led();
    gpio_set_level(BLUE_LED, 1);
    ESP_LOGI(TAG, "Internal LED OFF\n");
}


