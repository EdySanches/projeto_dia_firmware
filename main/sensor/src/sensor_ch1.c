/*
 * sensor.c
 *
 *  Created on: 7 de mai de 2023
 *      Author: edylu
 */

#include "sensor_ch1.h"

/* --------------- configuracao do modulo do sensor --------------- */
void sensor_s1_init(){

	adc1_config_width(ADC_WIDTH_BIT_12);
	adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11); //GPIO 36

}




/* --------------- configuracao do objeto sensor --------------- */
void s1_store_setpoint(uint32_t value_to_store)
{
    ESP_LOGI("s1_store_max_setpoint", "Armazenando %d", value_to_store);

    set_long_NVS_flash(SCH1_SETPOINT_NVS, (long)value_to_store);
//    SendDataBT((uint8_t *)"[CSOK]", strlen("[CSOK]"));
}

void s1_get_setpoint(uint32_t *value_to_store)
{
	get_long_NVS_flash(SCH1_SETPOINT_NVS, (long *)value_to_store);
}

void s1_store_average_setpoint(uint32_t value_to_store)
{
    ESP_LOGI("s1_store_average_setpoint", "Armazenando %d", value_to_store);

    set_long_NVS_flash(SCH1_AVERAGE_SETPOINT_NVS, (long)value_to_store);
//    SendDataBT((uint8_t *)"[CAOK]", strlen("[CAOK]"));
}

void s1_get_average_setpoint(uint32_t *value_to_store)
{
	get_long_NVS_flash(SCH1_AVERAGE_SETPOINT_NVS, (long *)value_to_store);
}

void s1_store_margin_setpoint(uint16_t margin_value)
{
    ESP_LOGI("s1_store_margin_setpoint", "Armazenando %d", margin_value);

    set_long_NVS_flash(SCH1_MARGIN_SETPOINT_NVS, (long)margin_value);
//    SendDataBT((uint8_t *)"[CMOK]", strlen("[CMOK]"));
}

void s1_get_margin_setpoint(uint16_t *margin_value)
{
	get_long_NVS_flash(SCH1_MARGIN_SETPOINT_NVS, (long *)margin_value);
}

void s1_store_acting_flag(bool flag)
{
	ESP_LOGI("s1_store_acting_flag", "Armazenando flag %i", flag);
	set_i8_NVS_flash(SCH1_ACTING_SETPOINT_NVS, (int8_t) flag);
//	SendDataBT((uint8_t *)"[CWOK]", strlen("[CWOK]"));
}

void s1_get_acting_flag(bool * flag)
{
	esp_err_t res = get_i8_NVS_flash(SCH1_ACTING_SETPOINT_NVS, (char *) flag);

	if (res != ESP_OK)
	{
		ESP_LOGW("s1_get_acting_flag", "Falha na consulta da atuacao, setando como falso");
		flag = false;
		s1_store_acting_flag(false);
	}
//	ESP_LOGW("ultra_get_acting_flag", "ESTADO: %s", (char *) flag);
}


/* declaracao do objeto sensor */
setpoint_base_t s1_setpoints =
{
	.channel = 1,
	.setpoint_high_value = 10,
	.setpoint_low_value = 1,
	.average_value = 8,
	.margin_value = 4,
	.acting_flag = false,
	.store_setpoint = s1_store_setpoint,
	.get_setpoint = s1_get_setpoint,
	.store_average_setpoint = s1_store_average_setpoint,
	.get_average_setpoint = s1_get_average_setpoint,
	.store_acting_flag = s1_store_acting_flag,
	.get_acting_flag = s1_get_acting_flag,
	.store_margin_setpoint = s1_store_margin_setpoint,
	.get_margin_setpoint = s1_get_margin_setpoint
};
