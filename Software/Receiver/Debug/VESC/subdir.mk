################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../VESC/VESC.c 

OBJS += \
./VESC/VESC.o 

C_DEPS += \
./VESC/VESC.d 


# Each subdirectory must supply rules for building sources it contributes
VESC/%.o VESC/%.su VESC/%.cyclo: ../VESC/%.c VESC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../Core/Inc -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Receiver/VESC" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Receiver/NRF24L01" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-VESC

clean-VESC:
	-$(RM) ./VESC/VESC.cyclo ./VESC/VESC.d ./VESC/VESC.o ./VESC/VESC.su

.PHONY: clean-VESC

