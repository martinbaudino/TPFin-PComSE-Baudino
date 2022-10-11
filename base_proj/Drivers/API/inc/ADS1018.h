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
#include "ADS1018_bsp.h"

/* Exported functions prototypes ---------------------------------------------*/
bool init_ads(void);
uint8_t read_ads(uint16_t *dataBuffer, uint8_t buffSize);


#endif /* API_INC_ADS1018_H_ */







