/*
 * setpoints.h
 *
 *  Created on: 8 de mai de 2023
 *      Author: edylu
 */

#ifndef MAIN_SENSOR_INC_SETPOINTS_H_
#define MAIN_SENSOR_INC_SETPOINTS_H_

#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <esp_err.h>


typedef struct _setpoint_base
{
    int channel;
    uint32_t setpoint_high_value;
    uint32_t setpoint_low_value;
    uint32_t average_value;
    uint16_t margin_value;
    bool acting_flag;


    void (*store_setpoint)(uint32_t value_to_store);
    void (*get_setpoint)(uint32_t * value_to_store);

    void (*store_average_setpoint)(uint32_t value_to_store);
    void (*get_average_setpoint)(uint32_t * value_to_store);

    void (*store_margin_setpoint)(uint16_t value_to_margin);
    void (*get_margin_setpoint)(uint16_t * value_to_margin);

    void (*store_acting_flag)(bool flag);
    void (*get_acting_flag)(bool * flag);

} setpoint_base_t;

extern setpoint_base_t s1_setpoints;
extern setpoint_base_t s2_setpoints;
extern setpoint_base_t s3_setpoints;
extern setpoint_base_t s4_setpoints;

setpoint_base_t * get_sensor_setpoint(uint8_t sensorCode);
//bool check_engspy_violation(ultrassonic_measures_t *ultra_measures);

#endif /* MAIN_SENSOR_INC_SETPOINTS_H_ */
