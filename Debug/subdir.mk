################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../gui.c \
../main.c 

OBJS += \
./gui.o \
./main.o 

C_DEPS += \
./gui.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/gtk-2.0 -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -export-dynamic  `pkg-config --cflags --libs gtk+-2.0` -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


