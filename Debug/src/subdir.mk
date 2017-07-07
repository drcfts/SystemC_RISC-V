################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/breg.cpp \
../src/cache.cpp \
../src/cache_pr.cpp \
../src/main.cpp \
../src/memoria.cpp \
../src/networkinterfacefrontendbase.cpp \
../src/shell_RISCV.cpp 

OBJS += \
./src/breg.o \
./src/cache.o \
./src/cache_pr.o \
./src/main.o \
./src/memoria.o \
./src/networkinterfacefrontendbase.o \
./src/shell_RISCV.o 

CPP_DEPS += \
./src/breg.d \
./src/cache.d \
./src/cache_pr.d \
./src/main.d \
./src/memoria.d \
./src/networkinterfacefrontendbase.d \
./src/shell_RISCV.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/systemc/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


