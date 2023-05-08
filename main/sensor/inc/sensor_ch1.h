/*
 * sensor.h
 *
 *  Created on: 7 de mai de 2023
 *      Author: edylu
 */

#ifndef MAIN_SENSOR_INC_SENSOR_CH1_H_
#define MAIN_SENSOR_INC_SENSOR_CH1_H_

/* libs */
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/semphr.h"
#include <driver/gpio.h>
#include <driver/adc.h>
#include <esp_err.h>
#include <esp_log.h>

#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#include "nvs_handler.h"
#include "setpoints.h"

/* defines */
#define SCH1_SETPOINT_NVS "SCH1setpoint"
#define SCH1_AVERAGE_SETPOINT_NVS "SCH1average"
#define SCH1_MARGIN_SETPOINT_NVS "SCH1margin"
#define SCH1_ACTING_SETPOINT_NVS "SCH1act"

/* tipos */
typedef struct s1_measures
{
 uint32_t sum_to_mean;
 uint32_t read_count;
 uint32_t read_sensor;
 float mean_sensor;
 uint16_t margin;

} sensor_s1_measures_t;

typedef struct
{
    gpio_num_t read_pin;
    gpio_num_t power_pin;
} sensor_s1_t;


/* funcoes */
//TODO constriur estas funcoes
void sensor_s1_init();
esp_err_t get_sensor_s1_read();

#endif /* MAIN_SENSOR_INC_SENSOR_CH1_H_ */
