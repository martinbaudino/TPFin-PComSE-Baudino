/*
 * comm_bsp.h
 *
 *  Created on: Oct 9, 2022
 *      Author: Martín Sebastián Baudino
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BSP_INC_COMM_BSP_H_
#define BSP_INC_COMM_BSP_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"  		/* <- HAL include */

/* Inclusión de tipos de datos de tamaño fijo */
#include <stdint.h>
#include <stdbool.h>

/* Para permitir el uso de **sprintf** antes de transmitir datos */
#include <stdio.h>

/* Exported functions prototypes ---------------------------------------------*/
bool init_uart(void);
bool tx_uart(uint8_t * dataBuffer);
bool rx_uart(uint8_t * dataBuffer, uint8_t buffSize);

#endif /* BSP_INC_COMM_BSP_H_ */
