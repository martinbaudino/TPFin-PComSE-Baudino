/*
 * ADS1018_bsp.h
 *
 *  Created on: Oct 9, 2022
 *      Author: marti
 */

#ifndef BSP_INC_ADS1018_BSP_H_
#define BSP_INC_ADS1018_BSP_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"


bool init_ads_spi(void);
uint16_t tx_rx_spi(uint16_t configWord);
// Adición ex post: convierte los canales con manejo de señales
// de bajo nivel
uint16_t read_ads_data(uint16_t *readBuffer, uint8_t buffSize);


#endif /* BSP_INC_ADS1018_BSP_H_ */
