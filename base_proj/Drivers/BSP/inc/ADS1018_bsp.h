/*
 * ADS1018_bsp.h
 *
 *  Created on: Oct 9, 2022
 *      Author: Martín Sebastián Baudino
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BSP_INC_ADS1018_BSP_H_
#define BSP_INC_ADS1018_BSP_H_

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

/* Exported constants --------------------------------------------------------*/
#define ADS_FULLDATA 3U
#define ADS_NODATA 	 0U

/* Exported functions prototypes ---------------------------------------------*/
bool init_ads_spi(void);
uint16_t tx_rx_spi(uint16_t configWord);
uint8_t read_ads_data(uint16_t *readBuffer, uint8_t buffSize);

#endif /* BSP_INC_ADS1018_BSP_H_ */
