/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <sensorApp.h>
#include "string.h"
#include <stdbool.h>
#include <stdint.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
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
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

ETH_TxPacketConfig TxConfig;
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

ETH_HandleTypeDef heth;

SPI_HandleTypeDef hspi4;

UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
//static void MX_SPI4_Init(void);
/* USER CODE BEGIN PFP */

/* ADS1018 */
bool init_ads(void);
uint8_t read_ads(uint16_t *dataBuffer, uint8_t buffSize);

/* ADS_BSP */
bool init_ads_spi(void);
uint16_t tx_rx_spi(uint16_t configWord);
// Adición ex post: convierte los canales con manejo de señales
// de bajo nivel
uint16_t read_ads_data(uint16_t *readBuffer, uint8_t buffSize);

/* SENS_COMM */
bool init_comm(void);
bool tx_data(uint8_t *dataBuffer);
bool rx_data(uint8_t *dataBuffer, uint8_t buffSize);

/* COMM_BSP */
bool init_uart(void);
bool tx_uart(uint8_t *dataBuffer, uint8_t buffSize);
bool rx_uart(uint8_t *dataBuffer, uint8_t buffSize);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint16_t MSP_Access_Data[3] = { 0 };
	uint16_t tin, tc1, tc2;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ETH_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
//  MX_SPI4_Init();
  /* USER CODE BEGIN 2 */
  init_ads();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  read_ads(MSP_Access_Data, 3);
	  //tin = (MSP_Access_Data[5] >> 4) + (((uint16_t)MSP_Access_Data[4]) << 4);
	 // tc1 = (MSP_Access_Data[3] >> 4) + (((uint16_t)MSP_Access_Data[2]) << 4);
	 // tc2 = (MSP_Access_Data[6] >> 1) + (((uint16_t)MSP_Access_Data[5]) << 0);
	 // HAL_UART_Transmit(&huart3, MSP_Access_Data, 6, 0xFFFF);
	  //HAL_UART_Transmit(&huart3, "\r\n", 2, 0xFFFF);

	  HAL_Delay(1000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

   static uint8_t MACAddr[6];

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  MACAddr[0] = 0x00;
  MACAddr[1] = 0x80;
  MACAddr[2] = 0xE1;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x00;
  MACAddr[5] = 0x00;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
  heth.Init.TxDesc = DMATxDscrTab;
  heth.Init.RxDesc = DMARxDscrTab;
  heth.Init.RxBuffLen = 1524;

  /* USER CODE BEGIN MACADDRESS */

  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }

  memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfig));
  TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
  TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
  TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

}

/**
  * @brief SPI4 Initialization Function
  * @param None
  * @retval None
  */
//static void MX_SPI4_Init(void)
//{
//
//  /* USER CODE BEGIN SPI4_Init 0 */
//
//  /* USER CODE END SPI4_Init 0 */
//
//  /* USER CODE BEGIN SPI4_Init 1 */
//
//  /* USER CODE END SPI4_Init 1 */
//  /* SPI4 parameter configuration*/
//  hspi4.Instance = SPI4;
//  hspi4.Init.Mode = SPI_MODE_MASTER;
//  hspi4.Init.Direction = SPI_DIRECTION_2LINES;
//  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
//  hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
//  hspi4.Init.CLKPhase = SPI_PHASE_2EDGE;
//  hspi4.Init.NSS = SPI_NSS_HARD_OUTPUT;
//  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
//  hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
//  hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
//  hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
//  hspi4.Init.CRCPolynomial = 10;
//  if (HAL_SPI_Init(&hspi4) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN SPI4_Init 2 */
//
//  /* USER CODE END SPI4_Init 2 */
//
//}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PF8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
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

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
