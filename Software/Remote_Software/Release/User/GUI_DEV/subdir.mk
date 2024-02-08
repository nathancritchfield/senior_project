################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/GUI_DEV/GUI_Paint.c 

OBJS += \
./User/GUI_DEV/GUI_Paint.o 

C_DEPS += \
./User/GUI_DEV/GUI_Paint.d 


# Each subdirectory must supply rules for building sources it contributes
User/GUI_DEV/%.o User/GUI_DEV/%.su User/GUI_DEV/%.cyclo: ../User/GUI_DEV/%.c User/GUI_DEV/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/LCD" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/Config" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/GUI_DEV" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/Fonts" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/example" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-GUI_DEV

clean-User-2f-GUI_DEV:
	-$(RM) ./User/GUI_DEV/GUI_Paint.cyclo ./User/GUI_DEV/GUI_Paint.d ./User/GUI_DEV/GUI_Paint.o ./User/GUI_DEV/GUI_Paint.su

.PHONY: clean-User-2f-GUI_DEV

