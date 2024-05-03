//
// Created by nikita on 03.05.24.
//

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "led_strip_control.h"

static led_strip_handle_t led_strip;

#define delay(x) vTaskDelay((x) / portTICK_PERIOD_MS)
#define FLOW 30
#define LED_STRIP_GPIO 7
#define LED_COUNT 125

void configure_led_strip(void)
{
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_STRIP_GPIO,
        .max_leds = LED_COUNT
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags.with_dma = false
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));

    led_strip_clear(led_strip);
}

void led_strip_set(hsb_t color_hsb)
{
    uint16_t hue = (uint16_t)color_hsb.hue;
    uint8_t saturation = (uint8_t)(color_hsb.saturation * 2.55);
    uint8_t value = (uint8_t)(color_hsb.brightness * 2.55);

    for(uint32_t index = 0; index < LED_COUNT; index++) {
        led_strip_set_pixel_hsv(led_strip, index, hue, saturation, value);
        led_strip_refresh(led_strip);
        delay(FLOW);

    }
    led_strip_refresh(led_strip);
}

void led_strip_reset(void)
{
    led_strip_clear(led_strip);
}