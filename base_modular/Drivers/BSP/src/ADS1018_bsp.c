/*
 * ADS1018_bsp.c
 *
 *  Created on: Oct 6, 2022
 *      Author: marti
 */

#include "ADS1018_bsp.h"
#include "stm32f4xx_hal.h"

/***************************** Definiciones de pines ***********************************/
#define     ADS1018_SPI_CLK             (0x0001)    // P3.0 Output: CLK para ADS1018
#define     ADS1018_SPI_SIMO            (0x0010)    // P3.4 Output: SIMO para ADS1018
#define     ADS1018_SPI_SOMI            (0x0020)    // P3.5 Input: SOMI para ADS1018
#define     ADS1018_SPI_SS              (0x0008)    // P4.3 Output: SS para ADS1018
#define     ADS1018_DRY                 (0x0008)    // P2.3 Input: DRY para ADS1018

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


static SPI_HandleTypeDef hspi4;


/**
 * @fn bool init_ads_spi(void)
 * @brief Inicializa puerto SPI para comunicación con ADS1018
 *
 * @return
 */
bool init_ads_spi(void){
	  /* USER CODE BEGIN SPI4_Init 0 */

	  /* USER CODE END SPI4_Init 0 */

	  /* USER CODE BEGIN SPI4_Init 1 */

	  /* USER CODE END SPI4_Init 1 */
	  /* SPI4 parameter configuration*/
	  hspi4.Instance = SPI4;
	  hspi4.Init.Mode = SPI_MODE_MASTER;
	  hspi4.Init.Direction = SPI_DIRECTION_2LINES;
	  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
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
	    Error_Handler();
	  }
	  /* USER CODE BEGIN SPI4_Init 2 */

	  /* USER CODE END SPI4_Init 2 */

}


/**
 * @fn uint8_t tx_rx_spi(uint8_t)
 * @brief Envía y recibe de a un byte en simultáneo por SPI
 *
 * @param configByte
 * @return
 */
uint8_t tx_rx_spi(uint8_t configByte){

}
