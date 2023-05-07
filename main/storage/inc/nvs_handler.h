#ifndef NVSHANDLER_H
#define NVSHANDLER_H
#include "esp_err.h"

#define BAIA_NVS "baiaidnvs"
#define INDEX_NVS "indexnvs"
#define TAGANT_NVS "tagantnvs"
#define MAXAMOSTAS_NVS "maxamostrasnvs"
#define RFID_PWR_NVS "rfidpwrnvs"
#define LOWER_REF_NVS "LowerRef"
#define HIGHER_REF_NVS "HigherRef"
#define MAX_AMOSTRAS_NVS "maxamostrasNVS"
#define MEDIAZERO_NVS "MediaZero"
#define MEDIAPESO_NVS "MediaPeso"
#define PESOCALIBRACAO_NVS "PesoCalibracao"
#define SSID_NVS "SSIDWIFI"
#define PASSWORD_NVS "PASSWORDWIFI"
#define DNS_NVS "dnsnvs"

/** @defgroup NVS 
 * 	Componente wrapper das funções nativas do NVS.
 *  @{
 */

#define ID_NVS "idarrobatech" /*!< Key para o ID da cmb salvo no NVS*/

/**
 * @brief Inicia a partição da memória NVS
 * 
 * @return ESP_OK: caso a inicialização seja feita \n ESP_FAIL: caso a inicialização falhe
 *  
 */
esp_err_t init_NVS_partition();

/**
 * @brief Realiza a leitura de um dado do tipo signed int de 8 bits da memória NVS
 * 
 * @param key[in] Nome da chave a ser lida
 * @param dataRead[out] Ponteiro onde será armezenada a leitura
 * 
 * @return 
 *  - ESP_OK: caso a leitura seja feita com sucesso;
 *  - ESP_FAIL: caso a leitura falhe;
 */
esp_err_t get_i8_NVS_flash(char * key, char * dataRead);

/**
 * @brief Realiza a leitura de um dado do tipo Long da memória NVS
 * 
 * @param key[in] Nome da chave a ser lida
 * @param dataRead[out] Ponteiro onde será armezenada a leitura
 * 
 * @return 
 * - ESP_OK: caso a leitura seja feita com sucesso;
 * - ESP_FAIL: caso a leitura falhe;
 */
esp_err_t get_long_NVS_flash(char * key, long * dataRead);

/**
 * @brief Realiza a leitura de um dado do tipo signed int de 16 bits da memória NVS
 * 
 * @param key[in] Nome da chave a ser lida
 * @param dataRead[out] Ponteiro onde será armezenada a leitura
 * 
 * @return 
 *  - ESP_OK: caso a leitura seja feita com sucesso;
 *  - ESP_FAIL: caso a leitura falhe;
 */
esp_err_t get_i16_NVS_flash(char * key, int16_t * dataRead);

/**
 * @brief Realiza a leitura de um char array da memória NVS
 * 
 * @param key[in] Nome da chave a ser lida
 * @param stringPointer[out] Ponteiro onde será armezenada a leitura
 * 
 * @return 
 *  - ESP_OK: caso a leitura seja feita com sucesso;
 *  - ESP_FAIL: caso a leitura falhe;
 */
esp_err_t get_blob_NVS_flash(char * key, char * stringPointer);

/**
 * @brief Realiza escrita de um dado do tipo Long da memória NVS
 * 
 * @param key[in] Nome da chave a ser escrita
 * @param dataToStore[out] Valor a ser escrito
 * 
 * @return 
 * - ESP_OK: caso a escrita seja feita com sucesso;
 * - ESP_FAIL: caso a escrita falhe;
 */
esp_err_t set_long_NVS_flash(char * key, long dataToStore);

/**
 * @brief Realiza escrita de um dado do tipo signed int de 16 bits da memória NVS
 * 
 * @param key[in] Nome da chave a ser escrita
 * @param dataToStore[in] Valor a ser escrito
 * 
 * @return 
 *  - ESP_OK: caso a escrita seja feita com sucesso;
 *  - ESP_FAIL: caso a escrita falhe;
 */
esp_err_t set_i16_NVS_flash(char * key, int16_t dataToStore);

/**
 * @brief Realiza escrita de um char array na memória NVS
 * 
 * @param key[in] Nome da chave a ser escrita
 * @param dataToStore[in] Valor a ser escrito
 * @param requiredSize[in] tamanho do char array a ser escrito
 * 
 * @return 
 *  - ESP_OK: caso a escrita seja feita com sucesso;
 *  - ESP_FAIL: caso a escrita falhe;
 */
esp_err_t set_blob_NVS_flash(char * key, char * dataToStore, int requiredSize);

/**
 * @brief Realiza escrita de um dado do tipo signed int de 8 bits da memória NVS
 * 
 * @param key[in] Nome da chave a ser escrita
 * @param dataToStore[in] Valor a ser escrito
 * 
 * @return 
 *  - ESP_OK: caso a escrita seja feita com sucesso;
 *  - ESP_FAIL: caso a escrita falhe;
 */
esp_err_t set_i8_NVS_flash(char * key, int8_t dataToStore);

/**
 * @brief Apaga uma dado da memória NVS
 * 
 * @param key[in] Nome da chave a ser apagada
 * 
 * @return 
 *  - ESP_OK: caso a escrita seja feita com sucesso;
 *  - ESP_FAIL: caso a escrita falhe;
 */
esp_err_t erase_NVS_key_flash(char * key);

#endif
/** @} */ 
