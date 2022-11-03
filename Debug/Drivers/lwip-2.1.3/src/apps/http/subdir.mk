################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lwip-2.1.3/src/apps/http/altcp_proxyconnect.c \
../Drivers/lwip-2.1.3/src/apps/http/fs.c \
../Drivers/lwip-2.1.3/src/apps/http/fsdata.c \
../Drivers/lwip-2.1.3/src/apps/http/http_client.c \
../Drivers/lwip-2.1.3/src/apps/http/httpd.c 

OBJS += \
./Drivers/lwip-2.1.3/src/apps/http/altcp_proxyconnect.o \
./Drivers/lwip-2.1.3/src/apps/http/fs.o \
./Drivers/lwip-2.1.3/src/apps/http/fsdata.o \
./Drivers/lwip-2.1.3/src/apps/http/http_client.o \
./Drivers/lwip-2.1.3/src/apps/http/httpd.o 

C_DEPS += \
./Drivers/lwip-2.1.3/src/apps/http/altcp_proxyconnect.d \
./Drivers/lwip-2.1.3/src/apps/http/fs.d \
./Drivers/lwip-2.1.3/src/apps/http/fsdata.d \
./Drivers/lwip-2.1.3/src/apps/http/http_client.d \
./Drivers/lwip-2.1.3/src/apps/http/httpd.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lwip-2.1.3/src/apps/http/%.o: ../Drivers/lwip-2.1.3/src/apps/http/%.c Drivers/lwip-2.1.3/src/apps/http/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L071xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/App" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RTT_Debug" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RingBuffer" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM/gsm_utilities" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32/arch" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/include" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/api" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/apps/http" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/apps/mdns" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/apps/mqtt" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip-2.1.3/src/apps/sntp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
