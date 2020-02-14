################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/stmpe1600/stmpe1600.c 

OBJS += \
./Drivers/BSP/Components/stmpe1600/stmpe1600.o 

C_DEPS += \
./Drivers/BSP/Components/stmpe1600/stmpe1600.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/stmpe1600/stmpe1600.o: ../Drivers/BSP/Components/stmpe1600/stmpe1600.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Drivers/CMSIS/Include -I"C:/Users/fouri/STM32Cube/Repository/STM32Cube_FW_F4_V1.24.2/Drivers/BSP/Components/ili9341" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"C:/Users/fouri/STM32Cube/Repository/STM32Cube_FW_F4_V1.24.2/Drivers/BSP/STM32F429I-Discovery" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/Components/stmpe1600/stmpe1600.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

