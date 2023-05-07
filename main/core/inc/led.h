/*
 * led.h
 *
 *  Created on: 5 de mai de 2023
 *      Author: edylu
 */

#ifndef MAIN_CORE_INC_LED_H_
#define MAIN_CORE_INC_LED_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
// #include "led_strip.h"
#include "sdkconfig.h"

/* defines */
#define BLINK_GPIO GPIO_NUM_2
#define GND_GPIO GPIO_NUM_4

void blink_led(uint8_t s_led_state);
void configure_led(void);


#endif /* MAIN_CORE_INC_LED_H_ */
