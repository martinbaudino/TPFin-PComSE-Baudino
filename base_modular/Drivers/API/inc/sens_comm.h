/*
 * sens_comm.h
 *
 *  Created on: Oct 6, 2022
 *      Author: marti
 */

#ifndef API_INC_SENS_COMM_H_
#define API_INC_SENS_COMM_H_

// Inicializa una interfaz de comunicación de manera
// transparente a la aplicación
bool init_comm(void);

// Transmite cadenas de caracteres terminadas en '\0'
bool tx_data(uint8_t *dataBuffer);

// Recibe cadenas de caracteres de tamaño definido
bool rx_data(uint8_t *dataBuffer, uint8_t buffSize);

#endif /* API_INC_SENS_COMM_H_ */
