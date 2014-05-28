################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Unit_Tests/test_BBox.cpp 

OBJS += \
./Unit_Tests/test_BBox.o 

CPP_DEPS += \
./Unit_Tests/test_BBox.d 


# Each subdirectory must supply rules for building sources it contributes
Unit_Tests/%.o: ../Unit_Tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/DavidsMac/Documents/cpp_workspace/Minipaint_redux/Assignment1_minipaint_redux/BBox" -I"/Users/DavidsMac/Documents/cpp_workspace/Minipaint_redux/Assignment1_minipaint_redux/Misc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


