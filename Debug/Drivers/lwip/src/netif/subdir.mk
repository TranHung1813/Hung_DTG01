################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lwip/src/netif/bridgeif.c \
../Drivers/lwip/src/netif/bridgeif_fdb.c \
../Drivers/lwip/src/netif/ethernet.c \
../Drivers/lwip/src/netif/lowpan6.c \
../Drivers/lwip/src/netif/lowpan6_ble.c \
../Drivers/lwip/src/netif/lowpan6_common.c \
../Drivers/lwip/src/netif/slipif.c \
../Drivers/lwip/src/netif/zepif.c 

OBJS += \
./Drivers/lwip/src/netif/bridgeif.o \
./Drivers/lwip/src/netif/bridgeif_fdb.o \
./Drivers/lwip/src/netif/ethernet.o \
./Drivers/lwip/src/netif/lowpan6.o \
./Drivers/lwip/src/netif/lowpan6_ble.o \
./Drivers/lwip/src/netif/lowpan6_common.o \
./Drivers/lwip/src/netif/slipif.o \
./Drivers/lwip/src/netif/zepif.o 

C_DEPS += \
./Drivers/lwip/src/netif/bridgeif.d \
./Drivers/lwip/src/netif/bridgeif_fdb.d \
./Drivers/lwip/src/netif/ethernet.d \
./Drivers/lwip/src/netif/lowpan6.d \
./Drivers/lwip/src/netif/lowpan6_ble.d \
./Drivers/lwip/src/netif/lowpan6_common.d \
./Drivers/lwip/src/netif/slipif.d \
./Drivers/lwip/src/netif/zepif.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lwip/src/netif/%.o: ../Drivers/lwip/src/netif/%.c Drivers/lwip/src/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L071xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/App" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RTT_Debug" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RingBuffer" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM/gsm_utilities" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32/arch" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/api" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/http" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mdns" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mqtt" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/sntp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core/ipv4" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/include/netif/ppp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

