/* bibliotecas */
#include "main.h"
#include <nvs.h>

/* defines */
#define BLINK_GPIO GPIO_NUM_2
#define GND_GPIO GPIO_NUM_4


/* globais */
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
    ESP_LOGI("configure_led", "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO);
    gpio_reset_pin(GND_GPIO);

    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(GND_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(GND_GPIO, 0);


}


/* aplicacao principal */
/* TODO list
 * - task de monitoramento
 * - sensor
 * - RTC
 * - timers
 * - headers http
 * - task de envio
 * */
void app_main(void)
{
	static const char *TAG = "app_main";
	ESP_LOGI(TAG, "Iniciando app_main...");

	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);


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
