################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/lis3dsh/lis3dsh.c 

OBJS += \
./Drivers/BSP/Components/lis3dsh/lis3dsh.o 

C_DEPS += \
./Drivers/BSP/Components/lis3dsh/lis3dsh.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/lis3dsh/lis3dsh.o: ../Drivers/BSP/Components/lis3dsh/lis3dsh.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Drivers/CMSIS/Include -I"C:/Users/fouri/STM32Cube/Repository/STM32Cube_FW_F4_V1.24.2/Drivers/BSP/Components/ili9341" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"C:/Users/fouri/STM32Cube/Repository/STM32Cube_FW_F4_V1.24.2/Drivers/BSP/STM32F429I-Discovery" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/Components/lis3dsh/lis3dsh.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

