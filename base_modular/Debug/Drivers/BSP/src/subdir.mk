################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/src/ADS1018_bsp.c \
../Drivers/BSP/src/comm_bsp.c 

OBJS += \
./Drivers/BSP/src/ADS1018_bsp.o \
./Drivers/BSP/src/comm_bsp.o 

C_DEPS += \
./Drivers/BSP/src/ADS1018_bsp.d \
./Drivers/BSP/src/comm_bsp.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/src/%.o Drivers/BSP/src/%.su: ../Drivers/BSP/src/%.c Drivers/BSP/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/API/inc -I../Drivers/BSP/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-src

clean-Drivers-2f-BSP-2f-src:
	-$(RM) ./Drivers/BSP/src/ADS1018_bsp.d ./Drivers/BSP/src/ADS1018_bsp.o ./Drivers/BSP/src/ADS1018_bsp.su ./Drivers/BSP/src/comm_bsp.d ./Drivers/BSP/src/comm_bsp.o ./Drivers/BSP/src/comm_bsp.su

.PHONY: clean-Drivers-2f-BSP-2f-src

