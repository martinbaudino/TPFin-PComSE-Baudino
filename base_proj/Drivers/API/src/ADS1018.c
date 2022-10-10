/*
 * ADS1018.c
 *
 *  Created on: Oct 9, 2022
 *      Author: marti
 */
#include "ADS1018.h"

bool init_ads(void){
	if(init_ads_spi() == true)
		return true;
	else
		return false;
}


uint8_t read_ads(uint16_t *dataBuffer, uint8_t buffSize){

	read_ads_data(dataBuffer, buffSize);

	return 6;
}


