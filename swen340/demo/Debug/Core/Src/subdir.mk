################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/LED.c \
../Core/Src/SysClock.c \
../Core/Src/UART.c \
../Core/Src/demo.c \
../Core/Src/gpio.c \
../Core/Src/hello_world.c \
../Core/Src/main.c \
../Core/Src/printf.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c 

OBJS += \
./Core/Src/LED.o \
./Core/Src/SysClock.o \
./Core/Src/UART.o \
./Core/Src/demo.o \
./Core/Src/gpio.o \
./Core/Src/hello_world.o \
./Core/Src/main.o \
./Core/Src/printf.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o 

C_DEPS += \
./Core/Src/LED.d \
./Core/Src/SysClock.d \
./Core/Src/UART.d \
./Core/Src/demo.d \
./Core/Src/gpio.d \
./Core/Src/hello_world.d \
./Core/Src/main.d \
./Core/Src/printf.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/LED.d ./Core/Src/LED.o ./Core/Src/SysClock.d ./Core/Src/SysClock.o ./Core/Src/UART.d ./Core/Src/UART.o ./Core/Src/demo.d ./Core/Src/demo.o ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/hello_world.d ./Core/Src/hello_world.o ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/printf.d ./Core/Src/printf.o ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o

.PHONY: clean-Core-2f-Src

