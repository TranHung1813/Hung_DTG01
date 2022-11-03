################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lwip/src/api/api_lib.c \
../Drivers/lwip/src/api/api_msg.c \
../Drivers/lwip/src/api/err.c \
../Drivers/lwip/src/api/if_api.c \
../Drivers/lwip/src/api/netbuf.c \
../Drivers/lwip/src/api/netdb.c \
../Drivers/lwip/src/api/netifapi.c \
../Drivers/lwip/src/api/sockets.c \
../Drivers/lwip/src/api/tcpip.c 

OBJS += \
./Drivers/lwip/src/api/api_lib.o \
./Drivers/lwip/src/api/api_msg.o \
./Drivers/lwip/src/api/err.o \
./Drivers/lwip/src/api/if_api.o \
./Drivers/lwip/src/api/netbuf.o \
./Drivers/lwip/src/api/netdb.o \
./Drivers/lwip/src/api/netifapi.o \
./Drivers/lwip/src/api/sockets.o \
./Drivers/lwip/src/api/tcpip.o 

C_DEPS += \
./Drivers/lwip/src/api/api_lib.d \
./Drivers/lwip/src/api/api_msg.d \
./Drivers/lwip/src/api/err.d \
./Drivers/lwip/src/api/if_api.d \
./Drivers/lwip/src/api/netbuf.d \
./Drivers/lwip/src/api/netdb.d \
./Drivers/lwip/src/api/netifapi.d \
./Drivers/lwip/src/api/sockets.d \
./Drivers/lwip/src/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lwip/src/api/%.o: ../Drivers/lwip/src/api/%.c Drivers/lwip/src/api/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L071xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/App" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RTT_Debug" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RingBuffer" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM/gsm_utilities" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32/arch" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/api" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/http" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mdns" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mqtt" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/sntp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core/ipv4" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/include/netif/ppp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

