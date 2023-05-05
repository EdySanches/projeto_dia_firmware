#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_intr_alloc.h"
#include "freertos/queue.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "nvs_handler.h"
#include "main.h"
#include "spiffshandler.h"


esp_err_t InitNVSDataPartition(){
	esp_err_t err_init = nvs_flash_init_partition("nvs_data");
	if(err_init != ESP_OK){
		nvs_flash_erase_partition("nvs_data");
		nvs_flash_init_partition("nvs_data");
	}
	return err_init;
}

esp_err_t GetLongNVSFlash(char * key, long * dataRead){
	nvs_handle my_handle;
	esp_err_t err;

	int32_t DadoArmazenado = 0;

	err = nvs_open_from_partition("nvs_data","storage", NVS_READWRITE, &my_handle);
	if (err != ESP_OK){
    	ESP_LOGE("GetLongNVSFlash", "Retornou ERR..");

		nvs_close(my_handle);
		return err;
	}

	err = nvs_get_i32(my_handle, key, &DadoArmazenado);
	if (err != ESP_OK){
    	ESP_LOGE("GetLongNVSFlash", "Retornou ERR..");

		nvs_close(my_handle);
		return err;
	}
	nvs_close(my_handle);

    *dataRead = (long)DadoArmazenado;

    return ESP_OK;
}

esp_err_t GetI16NVSFlash(char * key, int16_t * dataRead){
	nvs_handle my_handle;
	esp_err_t err;

	int16_t DadoArmazenado = 0;

	err = nvs_open_from_partition("nvs_data","storage", NVS_READWRITE, &my_handle);
	if (err != ESP_OK){
    	ESP_LOGE("GetInt16NVSFlash", "Retornou ERR..");

		nvs_close(my_handle);
		return err;
	}

	err = nvs_get_i16(my_handle, key, &DadoArmazenado);
	if (err != ESP_OK){
    	ESP_LOGE("GetInt16NVSFlash", "Retornou ERR..");

		nvs_close(my_handle);
		return err;
	}
	nvs_close(my_handle);
	*dataRead = DadoArmazenado;
    return ESP_OK;
}

esp_err_t GetI8NVSFlash(char * key, char * dataRead){
	nvs_handle my_handle;
	esp_err_t err;

	int8_t DadoArmazenado = 0;

	err = nvs_open_from_partition("nvs_data","storage", NVS_READWRITE, &my_handle);
	if (err != ESP_OK){
    	ESP_LOGE("GetInt8NVSFlash", "Retornou ERR..");

		nvs_close(my_handle);
		return err;
	}

	err = nvs_get_i8(my_handle, key, &DadoArmazenado);
	if (err != ESP_OK){
    	ESP_LOGE("GetInt8NVSFlash", "Retornou ERR..");

		nvs_close(my_handle);
		return err;
	}
	nvs_close(my_handle);

	*dataRead = DadoArmazenado;

    return ESP_OK;
}

esp_err_t GetBlobNVSFlash(char * key, char * stringPointer){
	nvs_handle my_handle;
	esp_err_t err;

    // Open
	err = nvs_open_from_partition("nvs_data","storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK){
    	ESP_LOGE("GetBlobNVSFlash", "Retornou ERR..");
		nvs_close(my_handle);

    	return err;
    }
	size_t required_size = 0;  // value will default to 0, if not set yet in NVS
	// obtain required memory space to store blob being read from NVS
	err = nvs_get_blob(my_handle, key, NULL, &required_size);
	if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) return err;
	if (required_size == 0) {
		stringPointer = "GenericData";
		nvs_close(my_handle);
		return ESP_FAIL;
	} else {
		err = nvs_get_blob(my_handle, key, stringPointer, &required_size);
		if (err != ESP_OK) {
			nvs_close(my_handle);
			return err;
		}
		stringPointer[required_size] = '\0';

	}
	ESP_LOGI("GetBlobNVSFlash", "Tamanho requerido para leitura: %d", required_size);
	// Close
	nvs_close(my_handle);
	return ESP_OK;
}

esp_err_t SetLongNVSFlash(char * key, long dataToStore){
    nvs_handle my_handle;
    esp_err_t err;

    // Open
    err = nvs_open_from_partition("nvs_data","storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK){
    	ESP_LOGE("SetLongNVSFlash", "Retornou ERR nvs_open_from_partition..");
		nvs_close(my_handle);
		return err;
    }

    err = nvs_set_i32(my_handle, key, dataToStore);
    if (err != ESP_OK){
    	ESP_LOGE("SetLongNVSFlash", "Retornou ERR nvs_set_i32..");

		nvs_close(my_handle);
		return err;
    }
   // Close
    nvs_close(my_handle);

    return ESP_OK;
}

esp_err_t SetI16NVSFlash(char * key, int16_t dataToStore){
    nvs_handle my_handle;
    esp_err_t err;

    // Open
    err = nvs_open_from_partition("nvs_data","storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK){
    	ESP_LOGE("SetI16NVSFlash", "Retornou ERR..");

		nvs_close(my_handle);
		return err;
    }

    err = nvs_set_i16(my_handle, key, dataToStore);
    if (err != ESP_OK){
    	ESP_LOGE("SetI16NVSFlash", "Retornou ERR..");

		nvs_close(my_handle);
		return err;
    }
   // Close
    nvs_close(my_handle);

    return ESP_OK;
}

esp_err_t SetI8NVSFlash(char * key, int8_t dataToStore){
    nvs_handle my_handle;
    esp_err_t err;

    // Open
    err = nvs_open_from_partition("nvs_data","storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK){
    	ESP_LOGE("SetI8NVSFlash", "Retornou ERR..");

		nvs_close(my_handle);
		return err;
    }

    err = nvs_set_i8(my_handle, key, dataToStore);
    if (err != ESP_OK){
    	ESP_LOGE("SetI8NVSFlash", "Retornou ERR..");
		nvs_close(my_handle);
		return err;
    }
   // Close
    nvs_close(my_handle);

    return ESP_OK;
}

esp_err_t SetBlobNVSFlash(char * key, char * dataToStore, int requiredSize){
	nvs_handle my_handle;
	esp_err_t err;

	// Open
	err = nvs_open_from_partition("nvs_data","storage", NVS_READWRITE, &my_handle);
	if (err != ESP_OK) {
    	ESP_LOGE("SetBlobNVSFlash", "Retornou ERR..");
		nvs_close(my_handle);
		return err;
	}
	err = nvs_set_blob(my_handle, key, dataToStore, requiredSize);

	if (err != ESP_OK) {
    	ESP_LOGE("SetBlobNVSFlash", "Retornou ERR..");

		nvs_close(my_handle);
		return err;
	}

	// Commit
	err = nvs_commit(my_handle);
	if (err != ESP_OK) {
    	ESP_LOGE("SetBlobNVSFlash", "Retornou ERR..");

		nvs_close(my_handle);
		return err;
	}
	// Close
	nvs_close(my_handle);
	return ESP_OK;
}


esp_err_t EraseNVSKeyFlash(char * key){
	nvs_handle my_handle;
	esp_err_t err;

	// Open
	err = nvs_open_from_partition("nvs_data","storage", NVS_READWRITE, &my_handle);
	if (err != ESP_OK) {
    	ESP_LOGE("EraseNVSKeyFlash", "Retornou ERR..");
		nvs_close(my_handle);
		return err;
	}

	err = nvs_erase_key(my_handle, key);
	if (err != ESP_OK) {
    	ESP_LOGE("EraseNVSKeyFlash", "Retornou ERR..");
		nvs_close(my_handle);
		return err;
	}


	nvs_close(my_handle);
	return ESP_OK;
}

