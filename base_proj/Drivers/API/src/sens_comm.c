/*
 * sens_comm.c
 *
 *  Created on: Oct 9, 2022
 *      Author: Martín Sebastián Baudino
 */

#include "sens_comm.h"

//
/**
 * @fn bool init_comm(void)
 * @brief Inicializa una interfaz de comunicación de manera abstracta
 *
 * @return Verdadero o falso, depende del resultado de la inicialización del
 * hardware específico
 */
bool init_comm(void) {
	return init_uart();
}

/**
 * @fn bool tx_data(uint8_t*)
 * @brief Transmite cadenas de caracteres terminadas en '\0'
 *
 * @param dataBuffer Memoria reservada para lectura de datos
 * @return Verdadero o falso, depende del resultado de la operación del
 * hardware
 */
bool tx_data(uint8_t *dataBuffer) {
	return tx_uart(dataBuffer);
}

/**
 * @fn bool rx_data(uint8_t*, uint8_t)
 * @brief Recibe cadenas de caracteres de tamaño definido
 *
 * @param dataBuffer
 * @param buffSize
 * @return Verdadero o falso, depende del resultado de la operación del
 * hardware
 */
bool rx_data(uint8_t *dataBuffer, uint8_t buffSize) {
	return rx_uart(dataBuffer, buffSize);
}
