/*
 * ADS1018_bsp.h
 *
 *  Created on: Oct 6, 2022
 *      Author: marti
 */

#ifndef BSP_INC_ADS1018_BSP_H_
#define BSP_INC_ADS1018_BSP_H_

#include <stdint.h>
#include <stdbool.h>



bool init_ads_spi(void);
uint8_t tx_rx_spi(uint8_t configByte);

#endif /* BSP_INC_ADS1018_BSP_H_ */
