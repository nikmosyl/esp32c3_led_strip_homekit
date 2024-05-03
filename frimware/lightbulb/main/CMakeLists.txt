idf_component_register(
        SRCS ./app_main.c ./lightbulb.c
        SRCS ./Libs/internal_led/internal_led.c
        SRCS Libs/led_strip/led_strip_control.c

        INCLUDE_DIRS "."
        INCLUDE_DIRS "Libs"
        INCLUDE_DIRS "Libs/internal_led"
        INCLUDE_DIRS "Libs/led_strip"
)
