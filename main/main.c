/* bibliotecas */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

#include "wifi.h"

/* defines */
#define BLINK_GPIO GPIO_NUM_13
#define GND_GPIO GPIO_NUM_4


/* globais */
static const char *TAG = "example";

static uint8_t s_led_state = 0;


/* funcoes auxiliares */
static void blink_led(uint8_t s_led_state)
{
    /* Set the GPIO level according to the state (LOW or HIGH)*/
//    gpio_set_level(BLINK_GPIO, s_led_state);
    gpio_set_level(BLINK_GPIO, s_led_state);
    vTaskDelay(100 / portTICK_PERIOD_MS);
//    gpio_set_level(GND_GPIO, 1);

}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO);
    gpio_reset_pin(GND_GPIO);

    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(GND_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(GND_GPIO, 0);


}


/* aplicacao principal */
/* TODO list
 * - NVS
 * - task de monitoramento
 * - sensor
 * - RTC
 * - timers
 * - headers http
 * - task de envio
 * */
void app_main(void)
{
	/* inicializa e conecta no wifi */
    wifi_init_sta();

    /* Configure the peripheral according to the LED type */
    configure_led();

    while (1) {
        ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
        blink_led(s_led_state);
        /* Toggle the LED state */
        s_led_state = !s_led_state;
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }

}
