/*
 * led.c
 *
 *  Created on: 5 de mai de 2023
 *      Author: edylu
 */

#include "led.h"

/* funcoes auxiliares */
void blink_led(uint8_t s_led_state)
{
    /* Set the GPIO level according to the state (LOW or HIGH)*/
//    gpio_set_level(BLINK_GPIO, s_led_state);
    gpio_set_level(BLINK_GPIO, s_led_state);
    vTaskDelay(100 / portTICK_PERIOD_MS);
//    gpio_set_level(GND_GPIO, 1);

}

void configure_led(void)
{
    ESP_LOGI("configure_led", "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO);
    gpio_reset_pin(GND_GPIO);

    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(GND_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(GND_GPIO, 0);


}
