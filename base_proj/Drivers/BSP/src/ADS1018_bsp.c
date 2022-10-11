/*
 * ADS1018_bsp.c
 *
 *  Created on: Oct 9, 2022
 *      Author: Martín Sebastián Baudino
 */

/* Includes ------------------------------------------------------------------*/
#include "ADS1018_bsp.h"

/* Private defines -----------------------------------------------------------*/
/**
 * @def ADS1018_CFG_XX
 * @brief Definiciones de bits de configuración del ADS1018 según hoja de datos
 *
 */
#define	ADS1018_CFG_SS		(0x8000)	// Single-shot conversion Start

#define ADS1018_CFG_CH1     (0x0000)	// Input multiplexer configuration:
// 000 = AINP is AIN0 and AINN is AIN1

#define ADS1018_CFG_CH2     (0x3000)	// Input multiplexer configuration:
// 011 = AINP is AIN2 and AINN is AIN3

#define ADS1018_CFG_PGA     (0x0E00)	// Programmable Gain Amplifier config
// 111 = FSR is ±0.256 V

#define ADS1018_CFG_MODE    (0x0100)	// Device operating mode:
// 1 = Power-down and single-shot mode

#define ADS1018_CFG_DR      (0x00A0)	// Data rate
// 110 = 3300 SPS

#define ADS1018_CFG_TINT    (0x0010)	// Temperature sensor mode
// 1 = Temperature sensor mode

#define ADS1018_CFG_PU_EN   (0x0008)	// Pullup resistor enable on DOUT/DRDY
// 1 = Pullup resistor enabled

#define ADS1018_CFG_NOP     (0x0002)	// NO OP: control if data are written
// 01 = Valid data; update Config register

#define ADS1018_CFG_RSV     (0x0001)	// Reserved
// Writing 0 or 1 has no effect

// Retardo máximo para Tx/Rx por SPI
#define MAX_TIMEOUT 0xFFFF

/* Private variables ---------------------------------------------------------*/

/**
 * Estructura para configuración y utilización de hardware SPI4
 */
static SPI_HandleTypeDef hspi4;

/* Exported functions --------------------------------------------------------*/

/**
 * @fn bool init_ads_spi(void)
 * @brief Inicialización del módulo de hardware SPI4, conectado a ADS1018
 *
 * Según la hoja de datos el ADS1018 trabaja con SPI en Modo 1, con el
 * reloj en bajo cuando está inactivo (CPOL=0), muestrea la señal de entrada
 * en flanco negativo y activa la de salida en el flanco positivo del reloj
 * (CPHA=1).
 *
 * @return Verdadero o falso, depende del resultado de la inicialización del
 * periférico SPI4
 */
bool init_ads_spi(void) {
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
	if (HAL_SPI_Init(&hspi4) == HAL_OK) {
		return true;
	}
	return false;
}

/**
 * @fn uint16_t tx_rx_spi(uint16_t)
 * @brief Transmisión y recepción de datos con el ADS1018 por SPI4
 *
 * IMPORTANTE: El ADS1018 opera sobre la línea MISO no solo para transmitir sus
 * lecturas, sino también para indicar que terminó de realizar una conversión.
 * Esto lo hace poniendo en alto la línea MISO cuando empieza a convertir y
 * luego en bajo cuando termina, en ambos casos con ausencia de clock cuando
 * se trata del modo de disparo único. Como se requiere realizar cuatro
 * mediciones consecutivas, se debe generar un ciclo BAJO-ALTO-BAJO entre
 * las mediciones de un tiempo suficientement corto como para que no se
 * generen pulsos de clock. Esto se hace con un retardo bloqueante de
 * alrededor de 600ns.
 *
 * @param configWord Palabra de configuración para captura del ADS1018
 * @return Valor adquirido según anterior palabra de configuración
 */
uint16_t tx_rx_spi(uint16_t configWord) {

	uint16_t response;
	uint8_t j;

	HAL_SPI_TransmitReceive(&hspi4, (uint8_t*) &configWord,
			(uint8_t*) &response, 1, MAX_TIMEOUT);

	/* Hace que el módulo SPI genere un pulso de 600ns sobre la señal de habilitación */
	__HAL_SPI_DISABLE(&hspi4);
	for (j = 0; j < 20; j++)
		;
	__HAL_SPI_ENABLE(&hspi4);

	return response;
}

/**
 * @fn uint8_t read_ads_data(uint16_t*, uint8_t)
 * @brief Convierte los canales con manejo de señales de bajo nivel
 *
 * Adición ex post: Para leer las mediciones del ADS1018 se debe enviar una
 * palabra de configuración que dispara la conversión analógica a digital.
 * Minentras eso sucede, se recibe el valor de la conversión anterior. Por
 * ello en esta configuración de disparo único, se envíean 4 palabras de
 * configuración, se descarta el primer dato, y la cuarta palabra de
 * configuración es un valor bobo solo para leer el resultado de la conversión.
 *
 * @param readBuffer Memoria reservada para lectura de datos
 * @param buffSize Cantidad de valores a leer
 * @return
 */
uint8_t read_ads_data(uint16_t *readBuffer, uint8_t buffSize) {

	uint16_t configADC[4] = {
	ADS1018_CFG_SS | ADS1018_CFG_CH2 | ADS1018_CFG_PGA | ADS1018_CFG_MODE
			| ADS1018_CFG_DR | ADS1018_CFG_PU_EN | ADS1018_CFG_NOP
			| ADS1018_CFG_RSV,
	ADS1018_CFG_SS | ADS1018_CFG_CH1 | ADS1018_CFG_PGA | ADS1018_CFG_MODE
			| ADS1018_CFG_DR | ADS1018_CFG_PU_EN | ADS1018_CFG_NOP
			| ADS1018_CFG_RSV,
	ADS1018_CFG_SS | ADS1018_CFG_TINT | ADS1018_CFG_PGA | ADS1018_CFG_MODE
			| ADS1018_CFG_DR | ADS1018_CFG_PU_EN | ADS1018_CFG_NOP
			| ADS1018_CFG_RSV, 0x0001 };
	uint8_t i;

	/** Envía la primera palabra de configuración. Se descarta el dato recibido
	 * porque es de la medición anterior
	 */
	tx_rx_spi(configADC[0]);

	/**
	 *  Envía las sucesivas palabras de configuración y recupera de los datos útiles
	 */
	for (i = 0; i < 3; i++) {
		// Espera que indique dato nuevo disponible
		while (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8) == 0)
			;
		while (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8) == 1)
			;
		/**
		 * El ADS1018 es un ADC de 12 bits y los valores adquiridos se
		 * encuentran en una palabra de 16 bits justificados a la izquierda,
		 * es necesario corregir esto antes de devolver los datos.
		 */
		readBuffer[i] = (tx_rx_spi(configADC[i + 1])) >> 4;
	}
	/**
	 * Al finalizar el ciclo de las 4 conversiones se deshabilita el módulo SPI
	 */
	__HAL_SPI_DISABLE(&hspi4);

	/**
	 * Devuelve siempre que se leyeron 3 datos
	 */
	return ADS_FULLDATA;
}

