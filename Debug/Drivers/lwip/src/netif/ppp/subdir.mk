################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lwip/src/netif/ppp/auth.c \
../Drivers/lwip/src/netif/ppp/ccp.c \
../Drivers/lwip/src/netif/ppp/chap-md5.c \
../Drivers/lwip/src/netif/ppp/chap-new.c \
../Drivers/lwip/src/netif/ppp/chap_ms.c \
../Drivers/lwip/src/netif/ppp/demand.c \
../Drivers/lwip/src/netif/ppp/eap.c \
../Drivers/lwip/src/netif/ppp/ecp.c \
../Drivers/lwip/src/netif/ppp/eui64.c \
../Drivers/lwip/src/netif/ppp/fsm.c \
../Drivers/lwip/src/netif/ppp/ipcp.c \
../Drivers/lwip/src/netif/ppp/ipv6cp.c \
../Drivers/lwip/src/netif/ppp/lcp.c \
../Drivers/lwip/src/netif/ppp/magic.c \
../Drivers/lwip/src/netif/ppp/mppe.c \
../Drivers/lwip/src/netif/ppp/multilink.c \
../Drivers/lwip/src/netif/ppp/ppp.c \
../Drivers/lwip/src/netif/ppp/pppapi.c \
../Drivers/lwip/src/netif/ppp/pppcrypt.c \
../Drivers/lwip/src/netif/ppp/pppoe.c \
../Drivers/lwip/src/netif/ppp/pppol2tp.c \
../Drivers/lwip/src/netif/ppp/pppos.c \
../Drivers/lwip/src/netif/ppp/upap.c \
../Drivers/lwip/src/netif/ppp/utils.c \
../Drivers/lwip/src/netif/ppp/vj.c 

OBJS += \
./Drivers/lwip/src/netif/ppp/auth.o \
./Drivers/lwip/src/netif/ppp/ccp.o \
./Drivers/lwip/src/netif/ppp/chap-md5.o \
./Drivers/lwip/src/netif/ppp/chap-new.o \
./Drivers/lwip/src/netif/ppp/chap_ms.o \
./Drivers/lwip/src/netif/ppp/demand.o \
./Drivers/lwip/src/netif/ppp/eap.o \
./Drivers/lwip/src/netif/ppp/ecp.o \
./Drivers/lwip/src/netif/ppp/eui64.o \
./Drivers/lwip/src/netif/ppp/fsm.o \
./Drivers/lwip/src/netif/ppp/ipcp.o \
./Drivers/lwip/src/netif/ppp/ipv6cp.o \
./Drivers/lwip/src/netif/ppp/lcp.o \
./Drivers/lwip/src/netif/ppp/magic.o \
./Drivers/lwip/src/netif/ppp/mppe.o \
./Drivers/lwip/src/netif/ppp/multilink.o \
./Drivers/lwip/src/netif/ppp/ppp.o \
./Drivers/lwip/src/netif/ppp/pppapi.o \
./Drivers/lwip/src/netif/ppp/pppcrypt.o \
./Drivers/lwip/src/netif/ppp/pppoe.o \
./Drivers/lwip/src/netif/ppp/pppol2tp.o \
./Drivers/lwip/src/netif/ppp/pppos.o \
./Drivers/lwip/src/netif/ppp/upap.o \
./Drivers/lwip/src/netif/ppp/utils.o \
./Drivers/lwip/src/netif/ppp/vj.o 

C_DEPS += \
./Drivers/lwip/src/netif/ppp/auth.d \
./Drivers/lwip/src/netif/ppp/ccp.d \
./Drivers/lwip/src/netif/ppp/chap-md5.d \
./Drivers/lwip/src/netif/ppp/chap-new.d \
./Drivers/lwip/src/netif/ppp/chap_ms.d \
./Drivers/lwip/src/netif/ppp/demand.d \
./Drivers/lwip/src/netif/ppp/eap.d \
./Drivers/lwip/src/netif/ppp/ecp.d \
./Drivers/lwip/src/netif/ppp/eui64.d \
./Drivers/lwip/src/netif/ppp/fsm.d \
./Drivers/lwip/src/netif/ppp/ipcp.d \
./Drivers/lwip/src/netif/ppp/ipv6cp.d \
./Drivers/lwip/src/netif/ppp/lcp.d \
./Drivers/lwip/src/netif/ppp/magic.d \
./Drivers/lwip/src/netif/ppp/mppe.d \
./Drivers/lwip/src/netif/ppp/multilink.d \
./Drivers/lwip/src/netif/ppp/ppp.d \
./Drivers/lwip/src/netif/ppp/pppapi.d \
./Drivers/lwip/src/netif/ppp/pppcrypt.d \
./Drivers/lwip/src/netif/ppp/pppoe.d \
./Drivers/lwip/src/netif/ppp/pppol2tp.d \
./Drivers/lwip/src/netif/ppp/pppos.d \
./Drivers/lwip/src/netif/ppp/upap.d \
./Drivers/lwip/src/netif/ppp/utils.d \
./Drivers/lwip/src/netif/ppp/vj.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lwip/src/netif/ppp/%.o: ../Drivers/lwip/src/netif/ppp/%.c Drivers/lwip/src/netif/ppp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L071xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/App" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RTT_Debug" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RingBuffer" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM/gsm_utilities" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32/arch" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/api" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/http" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mdns" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mqtt" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/sntp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core/ipv4" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/include/netif/ppp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

