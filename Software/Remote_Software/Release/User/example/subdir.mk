################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/example/LCD_1inch28_test.c 

OBJS += \
./User/example/LCD_1inch28_test.o 

C_DEPS += \
./User/example/LCD_1inch28_test.d 


# Each subdirectory must supply rules for building sources it contributes
User/example/%.o User/example/%.su User/example/%.cyclo: ../User/example/%.c User/example/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/LCD" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/Config" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/GUI_DEV" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/Fonts" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/example" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-example

clean-User-2f-example:
	-$(RM) ./User/example/LCD_1inch28_test.cyclo ./User/example/LCD_1inch28_test.d ./User/example/LCD_1inch28_test.o ./User/example/LCD_1inch28_test.su

.PHONY: clean-User-2f-example

