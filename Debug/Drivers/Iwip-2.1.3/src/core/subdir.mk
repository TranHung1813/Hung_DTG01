################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Iwip-2.1.3/src/core/altcp.c \
../Drivers/Iwip-2.1.3/src/core/altcp_alloc.c \
../Drivers/Iwip-2.1.3/src/core/altcp_tcp.c \
../Drivers/Iwip-2.1.3/src/core/def.c \
../Drivers/Iwip-2.1.3/src/core/dns.c \
../Drivers/Iwip-2.1.3/src/core/inet_chksum.c \
../Drivers/Iwip-2.1.3/src/core/init.c \
../Drivers/Iwip-2.1.3/src/core/ip.c \
../Drivers/Iwip-2.1.3/src/core/mem.c \
../Drivers/Iwip-2.1.3/src/core/memp.c \
../Drivers/Iwip-2.1.3/src/core/netif.c \
../Drivers/Iwip-2.1.3/src/core/pbuf.c \
../Drivers/Iwip-2.1.3/src/core/raw.c \
../Drivers/Iwip-2.1.3/src/core/stats.c \
../Drivers/Iwip-2.1.3/src/core/sys.c \
../Drivers/Iwip-2.1.3/src/core/tcp.c \
../Drivers/Iwip-2.1.3/src/core/tcp_in.c \
../Drivers/Iwip-2.1.3/src/core/tcp_out.c \
../Drivers/Iwip-2.1.3/src/core/timeouts.c \
../Drivers/Iwip-2.1.3/src/core/udp.c 

OBJS += \
./Drivers/Iwip-2.1.3/src/core/altcp.o \
./Drivers/Iwip-2.1.3/src/core/altcp_alloc.o \
./Drivers/Iwip-2.1.3/src/core/altcp_tcp.o \
./Drivers/Iwip-2.1.3/src/core/def.o \
./Drivers/Iwip-2.1.3/src/core/dns.o \
./Drivers/Iwip-2.1.3/src/core/inet_chksum.o \
./Drivers/Iwip-2.1.3/src/core/init.o \
./Drivers/Iwip-2.1.3/src/core/ip.o \
./Drivers/Iwip-2.1.3/src/core/mem.o \
./Drivers/Iwip-2.1.3/src/core/memp.o \
./Drivers/Iwip-2.1.3/src/core/netif.o \
./Drivers/Iwip-2.1.3/src/core/pbuf.o \
./Drivers/Iwip-2.1.3/src/core/raw.o \
./Drivers/Iwip-2.1.3/src/core/stats.o \
./Drivers/Iwip-2.1.3/src/core/sys.o \
./Drivers/Iwip-2.1.3/src/core/tcp.o \
./Drivers/Iwip-2.1.3/src/core/tcp_in.o \
./Drivers/Iwip-2.1.3/src/core/tcp_out.o \
./Drivers/Iwip-2.1.3/src/core/timeouts.o \
./Drivers/Iwip-2.1.3/src/core/udp.o 

C_DEPS += \
./Drivers/Iwip-2.1.3/src/core/altcp.d \
./Drivers/Iwip-2.1.3/src/core/altcp_alloc.d \
./Drivers/Iwip-2.1.3/src/core/altcp_tcp.d \
./Drivers/Iwip-2.1.3/src/core/def.d \
./Drivers/Iwip-2.1.3/src/core/dns.d \
./Drivers/Iwip-2.1.3/src/core/inet_chksum.d \
./Drivers/Iwip-2.1.3/src/core/init.d \
./Drivers/Iwip-2.1.3/src/core/ip.d \
./Drivers/Iwip-2.1.3/src/core/mem.d \
./Drivers/Iwip-2.1.3/src/core/memp.d \
./Drivers/Iwip-2.1.3/src/core/netif.d \
./Drivers/Iwip-2.1.3/src/core/pbuf.d \
./Drivers/Iwip-2.1.3/src/core/raw.d \
./Drivers/Iwip-2.1.3/src/core/stats.d \
./Drivers/Iwip-2.1.3/src/core/sys.d \
./Drivers/Iwip-2.1.3/src/core/tcp.d \
./Drivers/Iwip-2.1.3/src/core/tcp_in.d \
./Drivers/Iwip-2.1.3/src/core/tcp_out.d \
./Drivers/Iwip-2.1.3/src/core/timeouts.d \
./Drivers/Iwip-2.1.3/src/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Iwip-2.1.3/src/core/%.o: ../Drivers/Iwip-2.1.3/src/core/%.c Drivers/Iwip-2.1.3/src/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L071xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/App" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RTT_Debug" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RingBuffer" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM/gsm_utilities" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32/arch" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/api" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/apps/http" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/apps/mqtt" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/apps/mdns" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/apps/sntp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/netif" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/netif/ppp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/lwip" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/lwip/apps" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/lwip/priv" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/lwip/prot" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/core" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/core/ipv4" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/netif/ppp/polarssl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
