/*
 * comm_bsp.h
 *
 *  Created on: Oct 6, 2022
 *      Author: marti
 */

#ifndef BSP_INC_COMM_BSP_H_
#define BSP_INC_COMM_BSP_H_

// Inicializa puerto UART para comunicación con PC
bool init_uart(void);


// Envía cadenas de caracteres de tamaño específico por UART
bool tx_uart(uint8_t *dataBuffer, uint8_t buffSize);


// Recibe cadenas de caracteres de tamaño específico por UART
bool rx_uart(uint8_t *dataBuffer, uint8_t buffSize);

#endif /* BSP_INC_COMM_BSP_H_ */
