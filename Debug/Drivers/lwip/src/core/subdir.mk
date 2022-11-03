################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lwip/src/core/altcp.c \
../Drivers/lwip/src/core/altcp_alloc.c \
../Drivers/lwip/src/core/altcp_tcp.c \
../Drivers/lwip/src/core/def.c \
../Drivers/lwip/src/core/dns.c \
../Drivers/lwip/src/core/inet_chksum.c \
../Drivers/lwip/src/core/init.c \
../Drivers/lwip/src/core/ip.c \
../Drivers/lwip/src/core/mem.c \
../Drivers/lwip/src/core/memp.c \
../Drivers/lwip/src/core/netif.c \
../Drivers/lwip/src/core/pbuf.c \
../Drivers/lwip/src/core/raw.c \
../Drivers/lwip/src/core/stats.c \
../Drivers/lwip/src/core/sys.c \
../Drivers/lwip/src/core/tcp.c \
../Drivers/lwip/src/core/tcp_in.c \
../Drivers/lwip/src/core/tcp_out.c \
../Drivers/lwip/src/core/timeouts.c \
../Drivers/lwip/src/core/udp.c 

OBJS += \
./Drivers/lwip/src/core/altcp.o \
./Drivers/lwip/src/core/altcp_alloc.o \
./Drivers/lwip/src/core/altcp_tcp.o \
./Drivers/lwip/src/core/def.o \
./Drivers/lwip/src/core/dns.o \
./Drivers/lwip/src/core/inet_chksum.o \
./Drivers/lwip/src/core/init.o \
./Drivers/lwip/src/core/ip.o \
./Drivers/lwip/src/core/mem.o \
./Drivers/lwip/src/core/memp.o \
./Drivers/lwip/src/core/netif.o \
./Drivers/lwip/src/core/pbuf.o \
./Drivers/lwip/src/core/raw.o \
./Drivers/lwip/src/core/stats.o \
./Drivers/lwip/src/core/sys.o \
./Drivers/lwip/src/core/tcp.o \
./Drivers/lwip/src/core/tcp_in.o \
./Drivers/lwip/src/core/tcp_out.o \
./Drivers/lwip/src/core/timeouts.o \
./Drivers/lwip/src/core/udp.o 

C_DEPS += \
./Drivers/lwip/src/core/altcp.d \
./Drivers/lwip/src/core/altcp_alloc.d \
./Drivers/lwip/src/core/altcp_tcp.d \
./Drivers/lwip/src/core/def.d \
./Drivers/lwip/src/core/dns.d \
./Drivers/lwip/src/core/inet_chksum.d \
./Drivers/lwip/src/core/init.d \
./Drivers/lwip/src/core/ip.d \
./Drivers/lwip/src/core/mem.d \
./Drivers/lwip/src/core/memp.d \
./Drivers/lwip/src/core/netif.d \
./Drivers/lwip/src/core/pbuf.d \
./Drivers/lwip/src/core/raw.d \
./Drivers/lwip/src/core/stats.d \
./Drivers/lwip/src/core/sys.d \
./Drivers/lwip/src/core/tcp.d \
./Drivers/lwip/src/core/tcp_in.d \
./Drivers/lwip/src/core/tcp_out.d \
./Drivers/lwip/src/core/timeouts.d \
./Drivers/lwip/src/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lwip/src/core/%.o: ../Drivers/lwip/src/core/%.c Drivers/lwip/src/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L071xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/App" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RTT_Debug" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RingBuffer" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM/gsm_utilities" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32/arch" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/api" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/http" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mdns" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mqtt" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/sntp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core/ipv4" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/include/netif/ppp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

