################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/LCD/LCD_1inch28.c 

OBJS += \
./User/LCD/LCD_1inch28.o 

C_DEPS += \
./User/LCD/LCD_1inch28.d 


# Each subdirectory must supply rules for building sources it contributes
User/LCD/%.o User/LCD/%.su User/LCD/%.cyclo: ../User/LCD/%.c User/LCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/LCD" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/Config" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/GUI_DEV" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/Fonts" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/example" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/image" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-LCD

clean-User-2f-LCD:
	-$(RM) ./User/LCD/LCD_1inch28.cyclo ./User/LCD/LCD_1inch28.d ./User/LCD/LCD_1inch28.o ./User/LCD/LCD_1inch28.su

.PHONY: clean-User-2f-LCD

