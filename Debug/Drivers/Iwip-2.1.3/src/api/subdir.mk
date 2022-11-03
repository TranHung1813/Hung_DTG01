################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Iwip-2.1.3/src/api/api_lib.c \
../Drivers/Iwip-2.1.3/src/api/api_msg.c \
../Drivers/Iwip-2.1.3/src/api/err.c \
../Drivers/Iwip-2.1.3/src/api/if_api.c \
../Drivers/Iwip-2.1.3/src/api/netbuf.c \
../Drivers/Iwip-2.1.3/src/api/netdb.c \
../Drivers/Iwip-2.1.3/src/api/netifapi.c \
../Drivers/Iwip-2.1.3/src/api/sockets.c \
../Drivers/Iwip-2.1.3/src/api/tcpip.c 

OBJS += \
./Drivers/Iwip-2.1.3/src/api/api_lib.o \
./Drivers/Iwip-2.1.3/src/api/api_msg.o \
./Drivers/Iwip-2.1.3/src/api/err.o \
./Drivers/Iwip-2.1.3/src/api/if_api.o \
./Drivers/Iwip-2.1.3/src/api/netbuf.o \
./Drivers/Iwip-2.1.3/src/api/netdb.o \
./Drivers/Iwip-2.1.3/src/api/netifapi.o \
./Drivers/Iwip-2.1.3/src/api/sockets.o \
./Drivers/Iwip-2.1.3/src/api/tcpip.o 

C_DEPS += \
./Drivers/Iwip-2.1.3/src/api/api_lib.d \
./Drivers/Iwip-2.1.3/src/api/api_msg.d \
./Drivers/Iwip-2.1.3/src/api/err.d \
./Drivers/Iwip-2.1.3/src/api/if_api.d \
./Drivers/Iwip-2.1.3/src/api/netbuf.d \
./Drivers/Iwip-2.1.3/src/api/netdb.d \
./Drivers/Iwip-2.1.3/src/api/netifapi.d \
./Drivers/Iwip-2.1.3/src/api/sockets.d \
./Drivers/Iwip-2.1.3/src/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Iwip-2.1.3/src/api/%.o: ../Drivers/Iwip-2.1.3/src/api/%.c Drivers/Iwip-2.1.3/src/api/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L071xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/App" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RTT_Debug" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RingBuffer" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM/gsm_utilities" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32/arch" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/api" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/apps/http" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/apps/mqtt" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/apps/mdns" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/apps/sntp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/netif" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/netif/ppp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/lwip" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/lwip/apps" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/lwip/priv" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/lwip/prot" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/core" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/core/ipv4" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/Iwip-2.1.3/src/include/netif/ppp/polarssl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

