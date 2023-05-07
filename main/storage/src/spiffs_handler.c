/******************************************************************************
		* @file    spiffshandler.c
		* @author  Matheus Bueno Gomes
		* @brief   Biblioteca que gerencia o armazenamento circular de dados em memoria interna SPIFFS.
		* @owner   ENG SOLUCOES TECNOLOGICAS - LTDA ME
		* @lastmodified 22/05/2018
		@verbatim
*/

#include "spiffshandler.h"
#include "esp_system.h"
#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "esp_event.h"
#include "esp_log.h"
#include "math.h"
#include "main.h"


char CreateSPIFFSBlankFile(char * PATH, int initialSize){
	FILE * f;
	f = fopen(PATH, "r+b");

	if(f == NULL){
		fclose(f);
		ESP_LOGI("CreateSPIFFSDummyFile", "Arquivo %s nao criado, criando... Tamanho inicial: %d", PATH, initialSize);
		f = fopen(PATH, "a+");

		for(long i = 0; i < initialSize + 100; i++){
			fwrite("0", 1, strlen("0"), f);
			vTaskDelay(10/portTICK_RATE_MS);
		}

		fseek(f, 0L, SEEK_END);
		uint32_t tamanhoDados = ftell(f);
		ESP_LOGE("", "Tamanho dados: %d", tamanhoDados);

		fclose(f);

		if(tamanhoDados == initialSize) return 1;

		return 0;
	}else{
		ESP_LOGE("CreateSPIFFSDummyFile", "Arquivo já criado...");
		fclose(f);
		return 0;
	}
}
char isThisSPIFFSFileCreated(char * PATH){
	FILE * f;
	char fileCreated = 1;

	f = fopen(PATH, "r+b");
	if(f == NULL) fileCreated = 0;
	fclose(f);

	return  fileCreated;
}

char CreateSPIFFSFile(char * PATH, int initialSize, char initialContent[initialSize]){
	FILE * f;
	f = fopen(PATH, "r+b");

	if(f == NULL){
		fclose(f);
		ESP_LOGI("CreateSPIFFSFile", "Arquivo %s nao criado, criando... Tamanho inicial: %d", PATH, initialSize);
		f = fopen(PATH, "a+");

		fwrite(initialContent, 1, initialSize , f);

		fseek(f, 0L, SEEK_END);
		uint32_t tamanhoDados = ftell(f);
		ESP_LOGE("CreateSPIFFSFile", "Tamanho %s criado: %d",PATH, tamanhoDados);

		fclose(f);

		if(tamanhoDados == initialSize) return 1;

		return 0;
	}else{
		ESP_LOGE("CreateSPIFFSFile", "Arquivo ja criado...");
		fclose(f);
		return 0;
	}
}

void RemoveSPIFFSFile(char * PATH){
	remove(PATH);
}

char ReadDataSPIFFSFile(char * PATH, int pointer,int dataSize, char data[dataSize]){
	FILE * f;
    f = fopen(PATH, "r+b");

    if(f != NULL){
    	fseek(f, pointer, SEEK_SET);
    	fread((char *) data, dataSize, 1, f);
    	fclose(f);
    	return 1;
    }else{
    	fclose(f);
    	return 0;
    }
}

char WriteDataSPIFFSFile(char * PATH, int pointer, int dataSize, char data[dataSize], char checkData){
	FILE * f;
    f = fopen(PATH, "r+b");
    char returnFunc = 1;
    if(f != NULL){
    	fseek(f, pointer, SEEK_SET);
    	fwrite((char *) data, dataSize, 1, f);
    	/* Efetua a checagem se a chamada da funcao recebe para checar o que foi escrito eh igual ao lido */
    	if(checkData){
    		char dataRead[dataSize];
        	fseek(f, pointer, SEEK_SET);
    		fread((char *)dataRead, dataSize,1,f);


    		if(memcmp(dataRead, data, dataSize) == 0){
    			returnFunc = 1;
    		}else{
    			returnFunc = 0;
    			ESP_LOGE("WriteDataSPIFFSFile", "Erro comparacao escrito x lido.. Data Read: %s\r\n DataWrite: %s \r\n", dataRead, data);
    		}
    	}

    	fclose(f);
    	return returnFunc;
    }else{
    	fclose(f);
    	/* Retorna zero pois nao conseguiu abrir o arquivo */
    	return returnFunc;
    }
}

void InitSPIFFS(void){
	ESP_LOGI("", "Initializing SPIFFS");

	esp_vfs_spiffs_conf_t conf = { .base_path = "/spiffs", .partition_label =
			NULL, .max_files = 5, .format_if_mount_failed = true };
	/* Inicializa o SPIFFS */
	esp_err_t ret = esp_vfs_spiffs_register(&conf);

	/* Se nao conseguiu inicializar, reinicia o sistema */
	if (ret != ESP_OK) {
		if (ret == ESP_FAIL) {
			ESP_LOGE("", "Failed to mount or format filesystem");
			esp_restart();
		} else if (ret == ESP_ERR_NOT_FOUND) {
			ESP_LOGE("", "Failed to find SPIFFS partition");
			esp_restart();
		} else {
			ESP_LOGE("", "Failed to initialize SPIFFS (%s)",
					esp_err_to_name(ret));
			esp_restart();
		}
		return;
	}

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE("InitSPIFFS", "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI("InitSPIFFS", "Partition size: total: %d, used: %d", total, used);
    }
}
