################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Fonts/font16.c \
../User/Fonts/font24CN.c 

OBJS += \
./User/Fonts/font16.o \
./User/Fonts/font24CN.o 

C_DEPS += \
./User/Fonts/font16.d \
./User/Fonts/font24CN.d 


# Each subdirectory must supply rules for building sources it contributes
User/Fonts/%.o User/Fonts/%.su User/Fonts/%.cyclo: ../User/Fonts/%.c User/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/LCD" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/Config" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/GUI_DEV" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/Fonts" -I"C:/Users/nate_/Documents/Electric_Skateboard/Software/Remote_Software/User/example" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-User-2f-Fonts

clean-User-2f-Fonts:
	-$(RM) ./User/Fonts/font16.cyclo ./User/Fonts/font16.d ./User/Fonts/font16.o ./User/Fonts/font16.su ./User/Fonts/font24CN.cyclo ./User/Fonts/font24CN.d ./User/Fonts/font24CN.o ./User/Fonts/font24CN.su

.PHONY: clean-User-2f-Fonts

