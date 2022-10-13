/*
 * ADS1018.h
 *
 *  Created on: Oct 9, 2022
 *      Author: Martín Sebastián Baudino
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef API_INC_ADS1018_H_
#define API_INC_ADS1018_H_

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"


/* Exported functions prototypes ---------------------------------------------*/
bool init_ads(void);
uint8_t read_ads(uint16_t *dataBuffer, uint8_t buffSize);

/* Private function prototypes -----------------------------------------------*/
bool init_ads_spi(void);
uint16_t tx_rx_spi(uint16_t configWord);
uint8_t read_ads_data(uint16_t *readBuffer, uint8_t buffSize);

/* Exported constants --------------------------------------------------------*/
/** Cantidad de datos a leer: por ahora siempre se leen 3 valores */
#define ADS_FULLDATA 3U

/** Cantidad de datos leídos cuando hubo algún error, ninguno */
#define ADS_NODATA 	 0U


#endif /* API_INC_ADS1018_H_ */







