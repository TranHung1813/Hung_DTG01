################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/RTT_Debug/SEGGER_RTT.c \
../Drivers/RTT_Debug/SEGGER_RTT_printf.c 

S_UPPER_SRCS += \
../Drivers/RTT_Debug/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./Drivers/RTT_Debug/SEGGER_RTT.o \
./Drivers/RTT_Debug/SEGGER_RTT_ASM_ARMv7M.o \
./Drivers/RTT_Debug/SEGGER_RTT_printf.o 

S_UPPER_DEPS += \
./Drivers/RTT_Debug/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./Drivers/RTT_Debug/SEGGER_RTT.d \
./Drivers/RTT_Debug/SEGGER_RTT_printf.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/RTT_Debug/%.o: ../Drivers/RTT_Debug/%.c Drivers/RTT_Debug/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L071xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/App" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RTT_Debug" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RingBuffer" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM/gsm_utilities" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/RTT_Debug/%.o: ../Drivers/RTT_Debug/%.S Drivers/RTT_Debug/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
