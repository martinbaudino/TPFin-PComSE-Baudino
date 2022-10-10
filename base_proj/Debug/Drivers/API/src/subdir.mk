################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/src/ADS1018.c \
../Drivers/API/src/sens_comm.c 

OBJS += \
./Drivers/API/src/ADS1018.o \
./Drivers/API/src/sens_comm.o 

C_DEPS += \
./Drivers/API/src/ADS1018.d \
./Drivers/API/src/sens_comm.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/src/%.o Drivers/API/src/%.su: ../Drivers/API/src/%.c Drivers/API/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/API/inc -I../Drivers/BSP/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-src

clean-Drivers-2f-API-2f-src:
	-$(RM) ./Drivers/API/src/ADS1018.d ./Drivers/API/src/ADS1018.o ./Drivers/API/src/ADS1018.su ./Drivers/API/src/sens_comm.d ./Drivers/API/src/sens_comm.o ./Drivers/API/src/sens_comm.su

.PHONY: clean-Drivers-2f-API-2f-src

