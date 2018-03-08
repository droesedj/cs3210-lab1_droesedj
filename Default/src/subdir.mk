################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/STLfile.cpp \
../src/facet.cpp \
../src/main.cpp \
../src/solid.cpp \
../src/vertex.cpp 

OBJS += \
./src/STLfile.o \
./src/facet.o \
./src/main.o \
./src/solid.o \
./src/vertex.o 

CPP_DEPS += \
./src/STLfile.d \
./src/facet.d \
./src/main.d \
./src/solid.d \
./src/vertex.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


