//
// Created by nikita on 03.05.24.
//

#ifndef LIGHTBULB_LED_STRIP_CONTROL_H
#define LIGHTBULB_LED_STRIP_CONTROL_H

typedef struct hsb {
    float hue;  // 0-360
    float saturation;  // 0-100
    int brightness;  // 0-100
} hsb_t;

void configure_led_strip(void);

void led_strip_set(hsb_t);
void led_strip_reset(void);

#endif //LIGHTBULB_LED_STRIP_CONTROL_H
