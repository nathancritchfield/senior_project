################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../NRF24L01/NRF24L01.c 

OBJS += \
./NRF24L01/NRF24L01.o 

C_DEPS += \
./NRF24L01/NRF24L01.d 


# Each subdirectory must supply rules for building sources it contributes
NRF24L01/%.o NRF24L01/%.su NRF24L01/%.cyclo: ../NRF24L01/%.c NRF24L01/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/LCD" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/Config" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/GUI_DEV" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/Fonts" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/example" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/NRF24L01" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-NRF24L01

clean-NRF24L01:
	-$(RM) ./NRF24L01/NRF24L01.cyclo ./NRF24L01/NRF24L01.d ./NRF24L01/NRF24L01.o ./NRF24L01/NRF24L01.su

.PHONY: clean-NRF24L01

