################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Iwip-2.1.3/src/core/ipv4/autoip.c \
../Drivers/Iwip-2.1.3/src/core/ipv4/dhcp.c \
../Drivers/Iwip-2.1.3/src/core/ipv4/etharp.c \
../Drivers/Iwip-2.1.3/src/core/ipv4/icmp.c \
../Drivers/Iwip-2.1.3/src/core/ipv4/igmp.c \
../Drivers/Iwip-2.1.3/src/core/ipv4/ip4.c \
../Drivers/Iwip-2.1.3/src/core/ipv4/ip4_addr.c \
../Drivers/Iwip-2.1.3/src/core/ipv4/ip4_frag.c 

OBJS += \
./Drivers/Iwip-2.1.3/src/core/ipv4/autoip.o \
./Drivers/Iwip-2.1.3/src/core/ipv4/dhcp.o \
./Drivers/Iwip-2.1.3/src/core/ipv4/etharp.o \
./Drivers/Iwip-2.1.3/src/core/ipv4/icmp.o \
./Drivers/Iwip-2.1.3/src/core/ipv4/igmp.o \
./Drivers/Iwip-2.1.3/src/core/ipv4/ip4.o \
./Drivers/Iwip-2.1.3/src/core/ipv4/ip4_addr.o \
./Drivers/Iwip-2.1.3/src/core/ipv4/ip4_frag.o 

C_DEPS += \
./Drivers/Iwip-2.1.3/src/core/ipv4/autoip.d \
./Drivers/Iwip-2.1.3/src/core/ipv4/dhcp.d \
./Drivers/Iwip-2.1.3/src/core/ipv4/etharp.d \
./Drivers/Iwip-2.1.3/src/core/ipv4/icmp.d \
./Drivers/Iwip-2.1.3/src/core/ipv4/igmp.d \
./Drivers/Iwip-2.1.3/src/core/ipv4/ip4.d \
./Drivers/Iwip-2.1.3/src/core/ipv4/ip4_addr.d \
./Drivers/Iwip-2.1.3/src/core/ipv4/ip4_frag.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Iwip-2.1.3/src/core/ipv4/%.o: ../Drivers/Iwip-2.1.3/src/core/ipv4/%.c Drivers/Iwip-2.1.3/src/core/ipv4/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L071xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/App" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RTT_Debug" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RingBuffer" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM/gsm_utilities" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32/arch" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/api" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/apps/http" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/apps/mqtt" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/apps/mdns" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/apps/sntp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/netif" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/netif/ppp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/lwip" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/lwip/apps" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/lwip/priv" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/lwip/prot" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/core" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/core/ipv4" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/netif/ppp/polarssl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

