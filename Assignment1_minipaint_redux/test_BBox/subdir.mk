################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Canvas.cpp \
../GUI.cpp 

OBJS += \
./Canvas.o \
./GUI.o 

CPP_DEPS += \
./Canvas.d \
./GUI.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/DavidsMac/Documents/cpp_workspace/Minipaint_redux/Assignment1_minipaint_redux/BBox" -I"/Users/DavidsMac/Documents/cpp_workspace/Minipaint_redux/Assignment1_minipaint_redux/Misc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


