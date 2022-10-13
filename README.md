# TPFin-PComSE-Baudino

## Trabajo Práctico Final de la materia **Protocolos de Comunicación en Sistemas Embebidos**, cursada el cuarto bimestre de 2022

Alumno: **BAUDINO, Martín Sebastián**

Título del Trabajo Final: **Medición de temperatura por SPI con el ADC de bajo consumo ADS1018**


### Descripción General

El Circuito Integrado (IC) ADS1018, fabricado por Texas Instruments, es un Convertidor Analógico Digital (ADC) de 12 bits, con cuatro canales de entrada y la posibilidad de agruparlos de a pares para obtener dos entradas diferenciales. Además, cuenta con un Amplificador de Ganancia Programable (PGA) y un sensor de temperatura interno. Su principal aplicación es como interfaz de sensores de temperatura, especialmente termocuplas. Al mismo tiempo, su bajo consumo de potencia y la posibilidad de realizar un disparo único con auto apagado lo hace ideal para aplicaciones portables y su interfaz de comunicación SPI permite una sencilla conexión con cualquier tipo de microcontrolador.

Se implementa un sensor de temperatura de bajo consumo de disparo único utilizando la placa NUCLEO-F429ZI. Para ello se desarrollaron los drivers correspondientes según los requerimientos y el modelo aprendido durante el cursado de la materia, teniendo también en cuenta el código de referencia en lenguaje C que el fabricante ofrece para la familia de microcontroladores MSP432.
 
Para el desarrollo del prototipo se dispone de una placa NUCLEO-F429, un circuito impreso con un ADS1018, dos termocuplas, y un analizador lógico de bajo costo.

![Conexión de Termocuplas con ADS1018 ©Texas Instruments](01_Thermocouple_Setup_Edit.png)

La conexión de las termocuplas sigue el circuito propuesto por el fabricante y las conexiones con la placa nucleo se realizan de la siguiente manera:

| **ADS1018**  | **NUCLEO-F429**              |
|:------------:|:----------------------------:|
| SCLK         | PIN24 - PE_2 - **SPI4_SCK**  |
| /CS          | PIN23 - PE_4 - **SPI4_CS**   |
| DOUT/DRY     | PIN22 - PE_5 - **SPI4_MISO** | 
| DOUT/DRY     | PIN19 - PE_6 - **SPI4_MISO** |
| DIN          | PIN21 - PF_8 - **SPI4_MOSI** |

### Driver Desarrollado

Para cumplir con los requerimientos del trabajo integrador, se creó la siguiente esturctura de carpetas y archivos:

```
TPFin-PComSE-Baudino/    // Raiz del repositorio
|---ADS1018/             // Driver desarrollado
|   |---src/
|   |    |---ADS1018.c    // Funciones de alto nivel
|   |    |---port.c       // Funciones de acceso al hardware
|   |
|   |---inc/
|   |   |---ADS1018.h    // Interfaz pública del driver
|   |
|   |---docs/...         // Documentación del driver generada con Doxygen
|
|---base_proj/...        // Proyecto de ejemplo que utiliza el driver
```

* **ADS1018**: Funciones de la Interfaz de Programación de Aplicación de alto nivel del ADC ADS1018. 

```
// Inicializa el ADS1018 en modo de disparo único
bool init_ads(void);

// Dispara la conversión en los dos canales diferenciales
// del ADS1018 y espera los valores adquiridos
uint8_t read_ads(uint16_t *dataBuffer, uint8_t buffSize);
```

* **port**: Funciones de la Interfaz de bajo nivel utilizadas por la API para comunicarse con el ADS1018 a través de un puerto SPI del STM32F429ZI.
```
// Inicializa puerto SPI para comunicación con ADS1018
bool init_ads_spi(void);

// Adición ex post: convierte los canales con manejo de señales 
// de bajo nivel
uint8_t read_ads_data(uint16_t *readBuffer, uint8_t buffSize);

// Envía y recibe de a una palabra en simultáneo por SPI
uint16_t tx_rx_spi(uint16_t configWord);
```

* **Documentación**: Se utilizó el estilo Javadoc para generar documentación automática con Doxygen a partir de los comentarios de todas las constantes, variables y funciones del proyecto.

* **Proyecto de ejemplo**: La aplicación realiza mediciones de temperatura en dos termocuplas y el sensor de temperatura interno del ADS1018, comunicándose por SPI y luego retransmite estos valores a través de una interfaz UART. El microcontrolador se mantiene en modo Sleep y se despierta cada vez que se presiona el pulsador para ejecutar el ciclo de adquisición y transmisión de datos. 


### Mediciones Realizadas


![Captura de medición del sensor interno de temperatura del ADS1018](02_SPI_Read_Edit.png)



