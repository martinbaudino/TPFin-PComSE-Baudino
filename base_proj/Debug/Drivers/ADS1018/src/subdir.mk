################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ADS1018/src/ADS1018.c \
../Drivers/ADS1018/src/port.c 

OBJS += \
./Drivers/ADS1018/src/ADS1018.o \
./Drivers/ADS1018/src/port.o 

C_DEPS += \
./Drivers/ADS1018/src/ADS1018.d \
./Drivers/ADS1018/src/port.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ADS1018/src/%.o Drivers/ADS1018/src/%.su: ../Drivers/ADS1018/src/%.c Drivers/ADS1018/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/API/inc -I../Drivers/BSP/inc -I../Drivers/ADS1018/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ADS1018-2f-src

clean-Drivers-2f-ADS1018-2f-src:
	-$(RM) ./Drivers/ADS1018/src/ADS1018.d ./Drivers/ADS1018/src/ADS1018.o ./Drivers/ADS1018/src/ADS1018.su ./Drivers/ADS1018/src/port.d ./Drivers/ADS1018/src/port.o ./Drivers/ADS1018/src/port.su

.PHONY: clean-Drivers-2f-ADS1018-2f-src

