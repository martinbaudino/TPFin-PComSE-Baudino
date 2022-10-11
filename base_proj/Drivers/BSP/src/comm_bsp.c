/*
 * comm_bsp.c
 *
 *  Created on: Oct 9, 2022
 *      Author: Martín Sebastián Baudino
 */

/* Includes ------------------------------------------------------------------*/
#include "comm_bsp.h"
#include <stdlib.h>
#include <string.h>

/* Private defines -----------------------------------------------------------*/

#define MAX_TIMEOUT 0xFFFF	// Retardo máximo para Tx/Rx por UART

/* Private variables ---------------------------------------------------------*/

/**
 * Estructura para configuración y utilización de hardware UART3
 */
static UART_HandleTypeDef huart3;

/* Exported functions --------------------------------------------------------*/

/**
 * @fn bool_t init_uart(void)
 * @brief Inicialización de módulo UART que utiliza VirtualCOM port
 *
 * Configura la USART3 del STM32F429ZI, que en la placa NUCLEO está conectada
 * al VirtualCOM port y actúa como backchannel de comunicación entre la placa
 * y la PC utilizando el mismo cable USB con el que se programa el
 * microcontrolador.
 * Por defecto configura la comunicación como  8N1 @ 115200bps
 *
 * @return Verdadero si la configuración fue exitosa y falso si falló
 */
bool init_uart(void) {
	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART configured as follows:
	 - Word Length = 8 Bits (7 data bit + 1 parity bit) :
	 BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	 - Stop Bit    = One Stop bit
	 - Parity      = ODD parity
	 - BaudRate    = 9600 baud
	 - Hardware flow control disabled (RTS and CTS signals) */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&huart3) == HAL_OK) {
		tx_uart((uint8_t*) "UART3: 8N1 @ 115200\r\n");
		return true;
	}

	return true;
}

/**
 * @fn void tx_uart(uint8_t*)
 * @brief Transmite cadenas de caracteres de tamaño variable terminadas en '\0'
 *
 * Función insegura. Aunque chequea que el buffer tenga espacio reservado,
 * puede producir un buffer overflow si la cadena no está terminada en '\0'.
 *
 * @param dataBuffer Memoria reservada con cadena de caracteres a transmitir
 * @return Verdadero si la operación fue exitosa y falso si no lo fue
 */
bool tx_uart(uint8_t *dataBuffer) {
	uint8_t buffSize;

	if (dataBuffer != NULL) {
		buffSize = strlen((char*) dataBuffer);

		if (HAL_UART_Transmit(&huart3, dataBuffer, buffSize, MAX_TIMEOUT)
				== HAL_OK)
			return true;
	}
	return false;
}

/**
 * @fn bool rx_uart(uint8_t*, uint8_t)
 * @brief Recibe una cantidad solicitada de caracteres y los guarda en buffer
 *
 * No realiza ningún tipo de procesamiento sobre los datos recibidos
 *
 * @param dataBuffer Buffer de caracteres para guardar datos
 * @param buffSize Cantidad de datos a guardar
 * @return Verdadero si la operación fue exitosa y falso si no lo fue
 */
bool rx_uart(uint8_t *dataBuffer, uint8_t buffSize) {

	if (dataBuffer != NULL) {
		if (HAL_UART_Receive(&huart3, dataBuffer, buffSize, MAX_TIMEOUT)
				== HAL_OK)
			return true;
	}
	return false;
}
