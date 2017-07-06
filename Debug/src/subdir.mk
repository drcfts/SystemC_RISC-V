################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/breg.cpp \
../src/cache.cpp \
../src/main.cpp \
../src/memoria.cpp 

OBJS += \
./src/breg.o \
./src/cache.o \
./src/main.o \
./src/memoria.o 

CPP_DEPS += \
./src/breg.d \
./src/cache.d \
./src/main.d \
./src/memoria.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/systemc/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


