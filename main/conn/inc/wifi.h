/*
 * wifi.h
 *
 *  Created on: 3 de mai de 2023
 *      Author: edylu
 */

#ifndef MAIN_WIFI_H_
#define MAIN_WIFI_H_

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

#define WIFI_SSID      "TOPNETEdmar"
#define WIFI_PASS      "93917223"
#define MAXIMUM_RETRY  5


void wifi_init_sta(void);

#endif /* MAIN_WIFI_H_ */
