################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lwip/src/apps/http/altcp_proxyconnect.c \
../Drivers/lwip/src/apps/http/fs.c \
../Drivers/lwip/src/apps/http/fsdata.c \
../Drivers/lwip/src/apps/http/http_client.c \
../Drivers/lwip/src/apps/http/httpd.c 

OBJS += \
./Drivers/lwip/src/apps/http/altcp_proxyconnect.o \
./Drivers/lwip/src/apps/http/fs.o \
./Drivers/lwip/src/apps/http/fsdata.o \
./Drivers/lwip/src/apps/http/http_client.o \
./Drivers/lwip/src/apps/http/httpd.o 

C_DEPS += \
./Drivers/lwip/src/apps/http/altcp_proxyconnect.d \
./Drivers/lwip/src/apps/http/fs.d \
./Drivers/lwip/src/apps/http/fsdata.d \
./Drivers/lwip/src/apps/http/http_client.d \
./Drivers/lwip/src/apps/http/httpd.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lwip/src/apps/http/%.o: ../Drivers/lwip/src/apps/http/%.c Drivers/lwip/src/apps/http/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L071xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/App" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RTT_Debug" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RingBuffer" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM/gsm_utilities" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32/arch" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/api" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/http" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mdns" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mqtt" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/sntp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core/ipv4" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/include/netif/ppp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
