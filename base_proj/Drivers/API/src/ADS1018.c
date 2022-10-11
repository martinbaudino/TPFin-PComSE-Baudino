/*
 * ADS1018.c
 *
 *  Created on: Oct 9, 2022
 *      Author: Martín Sebastián Baudino
 */

/* Includes ------------------------------------------------------------------*/
#include "ADS1018.h"

/* Exported functions --------------------------------------------------------*/

/**
 * @fn bool init_ads(void)
 * @brief Inicializa el ADS1018 de manera abstracta
 *
 * @return Verdadero o falso, depende del resultado de la inicialización del
 * hardware específico
 */
bool init_ads(void) {
	return init_ads_spi();
}

/**
 * @fn uint8_t read_ads(uint16_t*, uint8_t)
 * @brief Lee el ADS1018 de manera abstracta
 *
 * @param dataBuffer Memoria reservada para lectura de datos
 * @param buffSize Cantidad de valores a leer
 * @return Verdadero o falso, depende del resultado de la lectura del hardware
 */
uint8_t read_ads(uint16_t *dataBuffer, uint8_t buffSize) {

	return read_ads_data(dataBuffer, buffSize);

}
