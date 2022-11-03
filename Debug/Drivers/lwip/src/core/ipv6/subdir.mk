################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lwip/src/core/ipv6/dhcp6.c \
../Drivers/lwip/src/core/ipv6/ethip6.c \
../Drivers/lwip/src/core/ipv6/icmp6.c \
../Drivers/lwip/src/core/ipv6/inet6.c \
../Drivers/lwip/src/core/ipv6/ip6.c \
../Drivers/lwip/src/core/ipv6/ip6_addr.c \
../Drivers/lwip/src/core/ipv6/ip6_frag.c \
../Drivers/lwip/src/core/ipv6/mld6.c \
../Drivers/lwip/src/core/ipv6/nd6.c 

OBJS += \
./Drivers/lwip/src/core/ipv6/dhcp6.o \
./Drivers/lwip/src/core/ipv6/ethip6.o \
./Drivers/lwip/src/core/ipv6/icmp6.o \
./Drivers/lwip/src/core/ipv6/inet6.o \
./Drivers/lwip/src/core/ipv6/ip6.o \
./Drivers/lwip/src/core/ipv6/ip6_addr.o \
./Drivers/lwip/src/core/ipv6/ip6_frag.o \
./Drivers/lwip/src/core/ipv6/mld6.o \
./Drivers/lwip/src/core/ipv6/nd6.o 

C_DEPS += \
./Drivers/lwip/src/core/ipv6/dhcp6.d \
./Drivers/lwip/src/core/ipv6/ethip6.d \
./Drivers/lwip/src/core/ipv6/icmp6.d \
./Drivers/lwip/src/core/ipv6/inet6.d \
./Drivers/lwip/src/core/ipv6/ip6.d \
./Drivers/lwip/src/core/ipv6/ip6_addr.d \
./Drivers/lwip/src/core/ipv6/ip6_frag.d \
./Drivers/lwip/src/core/ipv6/mld6.d \
./Drivers/lwip/src/core/ipv6/nd6.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lwip/src/core/ipv6/%.o: ../Drivers/lwip/src/core/ipv6/%.c Drivers/lwip/src/core/ipv6/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L071xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/App" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RTT_Debug" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RingBuffer" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM/gsm_utilities" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32/arch" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/api" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/http" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mdns" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mqtt" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/sntp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core/ipv4" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/include/netif/ppp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

