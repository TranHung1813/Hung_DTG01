################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lwip/src/core/ipv4/autoip.c \
../Drivers/lwip/src/core/ipv4/dhcp.c \
../Drivers/lwip/src/core/ipv4/etharp.c \
../Drivers/lwip/src/core/ipv4/icmp.c \
../Drivers/lwip/src/core/ipv4/igmp.c \
../Drivers/lwip/src/core/ipv4/ip4.c \
../Drivers/lwip/src/core/ipv4/ip4_addr.c \
../Drivers/lwip/src/core/ipv4/ip4_frag.c 

OBJS += \
./Drivers/lwip/src/core/ipv4/autoip.o \
./Drivers/lwip/src/core/ipv4/dhcp.o \
./Drivers/lwip/src/core/ipv4/etharp.o \
./Drivers/lwip/src/core/ipv4/icmp.o \
./Drivers/lwip/src/core/ipv4/igmp.o \
./Drivers/lwip/src/core/ipv4/ip4.o \
./Drivers/lwip/src/core/ipv4/ip4_addr.o \
./Drivers/lwip/src/core/ipv4/ip4_frag.o 

C_DEPS += \
./Drivers/lwip/src/core/ipv4/autoip.d \
./Drivers/lwip/src/core/ipv4/dhcp.d \
./Drivers/lwip/src/core/ipv4/etharp.d \
./Drivers/lwip/src/core/ipv4/icmp.d \
./Drivers/lwip/src/core/ipv4/igmp.d \
./Drivers/lwip/src/core/ipv4/ip4.d \
./Drivers/lwip/src/core/ipv4/ip4_addr.d \
./Drivers/lwip/src/core/ipv4/ip4_frag.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lwip/src/core/ipv4/%.o: ../Drivers/lwip/src/core/ipv4/%.c Drivers/lwip/src/core/ipv4/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L071xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/App" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RTT_Debug" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RingBuffer" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM/gsm_utilities" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32/arch" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/api" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/http" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mdns" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mqtt" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/sntp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core/ipv4" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/include/netif/ppp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

