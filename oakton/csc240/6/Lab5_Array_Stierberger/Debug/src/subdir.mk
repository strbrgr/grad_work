################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ItemType.cpp \
../src/StackType.cpp \
../src/StackTypeDriver.cpp 

CPP_DEPS += \
./src/ItemType.d \
./src/StackType.d \
./src/StackTypeDriver.d 

OBJS += \
./src/ItemType.o \
./src/StackType.o \
./src/StackTypeDriver.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/ItemType.d ./src/ItemType.o ./src/StackType.d ./src/StackType.o ./src/StackTypeDriver.d ./src/StackTypeDriver.o

.PHONY: clean-src

