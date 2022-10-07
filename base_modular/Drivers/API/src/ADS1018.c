/*
 * ADS1018.c
 *
 *  Created on: Oct 6, 2022
 *      Author: marti
 */

#include "ADS1018.h"

/**
 * @fn bool init_ads(void)
 * @brief Inicializa el ADS1018 en modo de disparo único
 *
 * @return
 */
bool init_ads(void) {

	init_ads_spi();
}


/**
 * @fn uint8_t read_ads(uint8_t*, uint8_t)
 * @brief Dispara la conversión en los dos canales diferenciales del ADS1018 y
 * 		  espera los valores adquiridos
 *
 * @param dataBuffer
 * @param buffSize
 * @return
 */
uint8_t read_ads(uint8_t *dataBuffer, uint8_t buffSize){

}

void leer_adc(uint8_t *data) {

	// TODO: cargar palabras de configuraci�n para el ADC
	uint16_t configADC[4] = { ADS1018_CFG_SS | ADS1018_CFG_CH2 | ADS1018_CFG_PGA
			| ADS1018_CFG_MODE | ADS1018_CFG_DR | ADS1018_CFG_PU_EN
			| ADS1018_CFG_NOP | ADS1018_CFG_RSV,
	ADS1018_CFG_SS | ADS1018_CFG_CH1 | ADS1018_CFG_PGA | ADS1018_CFG_MODE
			| ADS1018_CFG_DR | ADS1018_CFG_PU_EN | ADS1018_CFG_NOP
			| ADS1018_CFG_RSV,
	ADS1018_CFG_SS | ADS1018_CFG_TINT | ADS1018_CFG_PGA | ADS1018_CFG_MODE
			| ADS1018_CFG_DR | ADS1018_CFG_PU_EN | ADS1018_CFG_NOP
			| ADS1018_CFG_RSV, 0x0001 };
	uint8_t i, j;
	uint8_t dummy[3]= {0};

	uint8_t configADCinv[8] = {0};
	for (i = 0; i < 4; i++){
		configADCinv[i*2] = (uint8_t)(configADC[i] >> 8);
		configADCinv[(i*2)+1] = (uint8_t)(configADC[i]);
	}

	/* Env�o la primera palabra de configuraci�n y descarto el dato recibido */


	//SPI_Tx_Rx(configADC[0] >> 8);     // MSB
	//SPI_Tx_Rx(configADC[0]);          // LSB
	HAL_SPI_TransmitReceive(&hspi4, configADCinv, dummy, 2, 0xFFFFFFFF );

	__HAL_SPI_DISABLE(&hspi4);
	for (j = 0; j < 20; j++)
		;
	__HAL_SPI_ENABLE(&hspi4);



	/* Env�o de las sucesivas palabras de configuraci�n y recuperaci�n de los datos �tiles */

	for (i = 0; i < 3; i++) {
		// Espero que indique dato nuevo disponible
		while (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8) == 0)
			;
		//while (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4)	== GPIO_INPUT_PIN_HIGH)
		while (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8) == 1)
			;

		//data[(i * 2) + 1] = SPI_Tx_Rx(configADC[i + 1] >> 8);
		//data[(i * 2)] = SPI_Tx_Rx(configADC[i + 1]);
		HAL_SPI_TransmitReceive(&hspi4, &configADCinv[(i+1)*2], (data+(i*2)), 2, 0xFFFFFFFF );


		__HAL_SPI_DISABLE(&hspi4);
		for (j = 0; j < 20; j++)
			;
		__HAL_SPI_ENABLE(&hspi4);
	}
	__HAL_SPI_DISABLE(&hspi4);
}
