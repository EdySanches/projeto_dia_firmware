/*
 * sensor.h
 *
 *  Created on: 7 de mai de 2023
 *      Author: edylu
 */

#ifndef MAIN_SENSOR_INC_SENSOR_H_
#define MAIN_SENSOR_INC_SENSOR_H_

/* libs */
#include <stdint.h>
#include <inttypes.h>

typedef struct {
	uint8_t type;
	uint8_t channel;
	uint32_t value;
}sensor;

#endif /* MAIN_SENSOR_INC_SENSOR_H_ */
