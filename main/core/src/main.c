/* bibliotecas */
#include "main.h"

/* defines */


/* globais */
static uint8_t s_led_state = 0;


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
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }

}
