################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/breg.cpp \
../src/cache.cpp \
../src/main.cpp \
../src/memoria.cpp \
../src/memoria_instrucoes.cpp \
../src/networkinterfacefrontendbase.cpp \
../src/shell_Memoria.cpp \
../src/shell_RISCV.cpp 

OBJS += \
./src/breg.o \
./src/cache.o \
./src/main.o \
./src/memoria.o \
./src/memoria_instrucoes.o \
./src/networkinterfacefrontendbase.o \
./src/shell_Memoria.o \
./src/shell_RISCV.o 

CPP_DEPS += \
./src/breg.d \
./src/cache.d \
./src/main.d \
./src/memoria.d \
./src/memoria_instrucoes.d \
./src/networkinterfacefrontendbase.d \
./src/shell_Memoria.d \
./src/shell_RISCV.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/systemc-2.3.1a/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


