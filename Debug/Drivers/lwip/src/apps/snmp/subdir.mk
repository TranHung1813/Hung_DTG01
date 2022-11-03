################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lwip/src/apps/snmp/snmp_asn1.c \
../Drivers/lwip/src/apps/snmp/snmp_core.c \
../Drivers/lwip/src/apps/snmp/snmp_mib2.c \
../Drivers/lwip/src/apps/snmp/snmp_mib2_icmp.c \
../Drivers/lwip/src/apps/snmp/snmp_mib2_interfaces.c \
../Drivers/lwip/src/apps/snmp/snmp_mib2_ip.c \
../Drivers/lwip/src/apps/snmp/snmp_mib2_snmp.c \
../Drivers/lwip/src/apps/snmp/snmp_mib2_system.c \
../Drivers/lwip/src/apps/snmp/snmp_mib2_tcp.c \
../Drivers/lwip/src/apps/snmp/snmp_mib2_udp.c \
../Drivers/lwip/src/apps/snmp/snmp_msg.c \
../Drivers/lwip/src/apps/snmp/snmp_netconn.c \
../Drivers/lwip/src/apps/snmp/snmp_pbuf_stream.c \
../Drivers/lwip/src/apps/snmp/snmp_raw.c \
../Drivers/lwip/src/apps/snmp/snmp_scalar.c \
../Drivers/lwip/src/apps/snmp/snmp_snmpv2_framework.c \
../Drivers/lwip/src/apps/snmp/snmp_snmpv2_usm.c \
../Drivers/lwip/src/apps/snmp/snmp_table.c \
../Drivers/lwip/src/apps/snmp/snmp_threadsync.c \
../Drivers/lwip/src/apps/snmp/snmp_traps.c \
../Drivers/lwip/src/apps/snmp/snmpv3.c \
../Drivers/lwip/src/apps/snmp/snmpv3_mbedtls.c 

OBJS += \
./Drivers/lwip/src/apps/snmp/snmp_asn1.o \
./Drivers/lwip/src/apps/snmp/snmp_core.o \
./Drivers/lwip/src/apps/snmp/snmp_mib2.o \
./Drivers/lwip/src/apps/snmp/snmp_mib2_icmp.o \
./Drivers/lwip/src/apps/snmp/snmp_mib2_interfaces.o \
./Drivers/lwip/src/apps/snmp/snmp_mib2_ip.o \
./Drivers/lwip/src/apps/snmp/snmp_mib2_snmp.o \
./Drivers/lwip/src/apps/snmp/snmp_mib2_system.o \
./Drivers/lwip/src/apps/snmp/snmp_mib2_tcp.o \
./Drivers/lwip/src/apps/snmp/snmp_mib2_udp.o \
./Drivers/lwip/src/apps/snmp/snmp_msg.o \
./Drivers/lwip/src/apps/snmp/snmp_netconn.o \
./Drivers/lwip/src/apps/snmp/snmp_pbuf_stream.o \
./Drivers/lwip/src/apps/snmp/snmp_raw.o \
./Drivers/lwip/src/apps/snmp/snmp_scalar.o \
./Drivers/lwip/src/apps/snmp/snmp_snmpv2_framework.o \
./Drivers/lwip/src/apps/snmp/snmp_snmpv2_usm.o \
./Drivers/lwip/src/apps/snmp/snmp_table.o \
./Drivers/lwip/src/apps/snmp/snmp_threadsync.o \
./Drivers/lwip/src/apps/snmp/snmp_traps.o \
./Drivers/lwip/src/apps/snmp/snmpv3.o \
./Drivers/lwip/src/apps/snmp/snmpv3_mbedtls.o 

C_DEPS += \
./Drivers/lwip/src/apps/snmp/snmp_asn1.d \
./Drivers/lwip/src/apps/snmp/snmp_core.d \
./Drivers/lwip/src/apps/snmp/snmp_mib2.d \
./Drivers/lwip/src/apps/snmp/snmp_mib2_icmp.d \
./Drivers/lwip/src/apps/snmp/snmp_mib2_interfaces.d \
./Drivers/lwip/src/apps/snmp/snmp_mib2_ip.d \
./Drivers/lwip/src/apps/snmp/snmp_mib2_snmp.d \
./Drivers/lwip/src/apps/snmp/snmp_mib2_system.d \
./Drivers/lwip/src/apps/snmp/snmp_mib2_tcp.d \
./Drivers/lwip/src/apps/snmp/snmp_mib2_udp.d \
./Drivers/lwip/src/apps/snmp/snmp_msg.d \
./Drivers/lwip/src/apps/snmp/snmp_netconn.d \
./Drivers/lwip/src/apps/snmp/snmp_pbuf_stream.d \
./Drivers/lwip/src/apps/snmp/snmp_raw.d \
./Drivers/lwip/src/apps/snmp/snmp_scalar.d \
./Drivers/lwip/src/apps/snmp/snmp_snmpv2_framework.d \
./Drivers/lwip/src/apps/snmp/snmp_snmpv2_usm.d \
./Drivers/lwip/src/apps/snmp/snmp_table.d \
./Drivers/lwip/src/apps/snmp/snmp_threadsync.d \
./Drivers/lwip/src/apps/snmp/snmp_traps.d \
./Drivers/lwip/src/apps/snmp/snmpv3.d \
./Drivers/lwip/src/apps/snmp/snmpv3_mbedtls.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lwip/src/apps/snmp/%.o: ../Drivers/lwip/src/apps/snmp/%.c Drivers/lwip/src/apps/snmp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L071xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/App" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RTT_Debug" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/RingBuffer" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/GSM/gsm_utilities" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/stm32/arch" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/api" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/http" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mdns" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/mqtt" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/apps/sntp" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/core/ipv4" -I"C:/Users/Administrator/Desktop/Stm32 Projects/Hung_DTG01_Git/Drivers/lwip/src/include/netif/ppp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

