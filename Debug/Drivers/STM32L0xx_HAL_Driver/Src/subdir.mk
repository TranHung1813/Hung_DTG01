################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_cortex.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_dma.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_exti.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash_ex.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash_ramfunc.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_gpio.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2c.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2c_ex.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pwr.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pwr_ex.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rcc.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rcc_ex.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tim.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tim_ex.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_uart.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_uart_ex.c 

OBJS += \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_cortex.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_dma.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_exti.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash_ex.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash_ramfunc.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_gpio.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2c.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2c_ex.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pwr.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pwr_ex.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rcc.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rcc_ex.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tim.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tim_ex.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_uart.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_uart_ex.o 

C_DEPS += \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_cortex.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_dma.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_exti.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash_ex.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash_ramfunc.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_gpio.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2c.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2c_ex.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pwr.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pwr_ex.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rcc.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rcc_ex.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tim.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tim_ex.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_uart.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_uart_ex.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32L0xx_HAL_Driver/Src/%.o: ../Drivers/STM32L0xx_HAL_Driver/Src/%.c Drivers/STM32L0xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L071xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/App" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RTT_Debug" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RingBuffer" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM/gsm_utilities" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32/arch" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/include" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/api" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/apps/mdns" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/apps/mqtt" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/apps/sntp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/core" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/core/ipv4" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/include/netif" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/include/netif/ppp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/include/netif/ppp/polarssl" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/include/lwip" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/include/lwip/apps" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/include/lwip/priv" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/include/lwip/prot" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/netif/ppp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/netif/ppp/polarssl" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/mqtt_client" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/http_client" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/apps/http" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

