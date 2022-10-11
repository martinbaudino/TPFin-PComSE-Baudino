/*
 * sens_comm.h
 *
 *  Created on: Oct 9, 2022
 *      Author: Martín Sebastián Baudino
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef API_INC_SENS_COMM_H_
#define API_INC_SENS_COMM_H_

/* Includes ------------------------------------------------------------------*/
#include "comm_bsp.h"

/* Exported functions prototypes ---------------------------------------------*/
bool init_comm(void);
bool tx_data(uint8_t *dataBuffer);
bool rx_data(uint8_t *dataBuffer, uint8_t buffSize);

#endif /* API_INC_SENS_COMM_H_ */
