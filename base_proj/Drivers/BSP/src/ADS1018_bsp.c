/*
 * ADS1018_bsp.c
 *
 *  Created on: Oct 9, 2022
 *      Author: marti
 */

#include "ADS1018_bsp.h"

/***************************** Definiciones de pines ***********************************/
//#define     ADS1018_SPI_CLK             (0x0001)    // P3.0 Output: CLK para ADS1018
//#define     ADS1018_SPI_SIMO            (0x0010)    // P3.4 Output: SIMO para ADS1018
//#define     ADS1018_SPI_SOMI            (0x0020)    // P3.5 Input: SOMI para ADS1018
//#define     ADS1018_SPI_SS              (0x0008)    // P4.3 Output: SS para ADS1018
//#define     ADS1018_DRY                 (0x0008)    // P2.3 Input: DRY para ADS1018

#define     ADS1018_CFG_SS              (0x8000)
#define     ADS1018_CFG_CH1             (0x0000)
#define     ADS1018_CFG_CH2             (0x3000)
#define     ADS1018_CFG_TINT            (0x0010)
#define     ADS1018_CFG_PGA             (0x0E00)
#define     ADS1018_CFG_MODE            (0x0100)
#define     ADS1018_CFG_DR              (0x00A0)
#define     ADS1018_CFG_PU_EN           (0x0008)
#define     ADS1018_CFG_NOP             (0x0002)
#define     ADS1018_CFG_RSV             (0x0001)

SPI_HandleTypeDef hspi4;

bool init_ads_spi(void){
	  hspi4.Instance = SPI4;
	  hspi4.Init.Mode = SPI_MODE_MASTER;
	  hspi4.Init.Direction = SPI_DIRECTION_2LINES;
	  hspi4.Init.DataSize = SPI_DATASIZE_16BIT;
	  hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
	  hspi4.Init.CLKPhase = SPI_PHASE_2EDGE;
	  hspi4.Init.NSS = SPI_NSS_HARD_OUTPUT;
	  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	  hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
	  hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
	  hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	  hspi4.Init.CRCPolynomial = 10;
	  if (HAL_SPI_Init(&hspi4) != HAL_OK)
	  {
	    return false;
	  }
	  return true;
}


uint16_t tx_rx_spi(uint16_t configWord){

	uint16_t response;
	uint8_t j;

	HAL_SPI_TransmitReceive(&hspi4, (uint8_t *)&configWord, (uint8_t *)&response, 1, 0xFFFFFFFF );

	__HAL_SPI_DISABLE(&hspi4);
	for (j = 0; j < 20; j++)
		;
	__HAL_SPI_ENABLE(&hspi4);

	return response;
}


// Adición ex post: convierte los canales con manejo de señales
// de bajo nivel
uint16_t read_ads_data(uint16_t *readBuffer, uint8_t buffSize) {

	uint16_t configADC[4] = {
			ADS1018_CFG_SS | ADS1018_CFG_CH2 | ADS1018_CFG_PGA | ADS1018_CFG_MODE | ADS1018_CFG_DR | ADS1018_CFG_PU_EN | ADS1018_CFG_NOP | ADS1018_CFG_RSV,
			ADS1018_CFG_SS | ADS1018_CFG_CH1 | ADS1018_CFG_PGA | ADS1018_CFG_MODE | ADS1018_CFG_DR | ADS1018_CFG_PU_EN | ADS1018_CFG_NOP | ADS1018_CFG_RSV,
			ADS1018_CFG_SS | ADS1018_CFG_TINT| ADS1018_CFG_PGA | ADS1018_CFG_MODE | ADS1018_CFG_DR | ADS1018_CFG_PU_EN | ADS1018_CFG_NOP | ADS1018_CFG_RSV,
			0x0001 };
	uint8_t i;

	/** Envía la primera palabra de configuración. Se descarta el dato recibido
	 * porque es de la medición anterior */
	tx_rx_spi(configADC[0]);

	/* Envía las sucesivas palabras de configuración y recupera de los datos útiles */
	for (i = 0; i < 3; i++) {
		// Espera que indique dato nuevo disponible
		while (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8) == 0)
			;
		while (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8) == 1)
			;

		readBuffer[i] = (tx_rx_spi(configADC[i + 1])) >> 4;
	}
	__HAL_SPI_DISABLE(&hspi4);
	return 6;
}
