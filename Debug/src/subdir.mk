################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/SHELL_MEM_RISC.cpp \
../src/breg.cpp \
../src/main.cpp \
../src/memoria.cpp \
../src/networkinterfacefrontendbase.cpp \
../src/shell_Memoria.cpp \
../src/shell_RISCV.cpp \
../src/specialkernel.cpp 

OBJS += \
./src/SHELL_MEM_RISC.o \
./src/breg.o \
./src/main.o \
./src/memoria.o \
./src/networkinterfacefrontendbase.o \
./src/shell_Memoria.o \
./src/shell_RISCV.o \
./src/specialkernel.o 

CPP_DEPS += \
./src/SHELL_MEM_RISC.d \
./src/breg.d \
./src/main.d \
./src/memoria.d \
./src/networkinterfacefrontendbase.d \
./src/shell_Memoria.d \
./src/shell_RISCV.d \
./src/specialkernel.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/systemc/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


